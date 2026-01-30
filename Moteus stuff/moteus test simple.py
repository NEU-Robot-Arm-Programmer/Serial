#!/usr/bin/python3 -B
import asyncio
import math
import moteus
import time 

SERVO_IDS = [1]   # <— set your two IDs here

SERVO_UUIDs = ['dd11039b']

TORQUE_SCALING_FACTOR = (.73/.9)

async def main():
    # (Optional) keep your extra telemetry if you still want it
    qr = moteus.QueryResolution()
    qr._extra = { moteus.Register.Q_CURRENT: moteus.F32 }

    q1 = moteus.Controller(moteus.DeviceAddress(uuid=bytes.fromhex(SERVO_UUIDs[0])),query_resolution=qr)

    #await c.set_stop()

    # Two controllers
    #c = [moteus.Controller(id=i, query_resolution=qr) for i in SERVO_IDS]
    c = [q1]#,q2,q3]

    await asyncio.gather(*(ctl.set_recapture_position_velocity() for ctl in c))

    position = await asyncio.gather(*(ctl.query() for ctl in c))

    print(position[0])
    
    # Clear faults on both
    await asyncio.gather(*(ctl.set_stop() for ctl in c))
    

    try:
        while True:
            # Hold current position on both, and query defaults
            current_command = -.02

            states = []
            for ctl in c:

                states.append(ctl.set_position(
                    position=current_command,
                    #velocity=0,
                    accel_limit=1.0,
                    maximum_torque = 3.0*TORQUE_SCALING_FACTOR,
                    velocity_limit=1.0,
                    query=True,
                ))

            results = await asyncio.gather(*states)

            # Print per-servo position/velocity
            for i, st in zip(SERVO_IDS, results):
                tor = st.values[moteus.Register.TORQUE]#/TORQUE_SCALING_FACTOR
                pos = st.values[moteus.Register.POSITION]
                cur = st.values[moteus.Register.Q_CURRENT]
                fault = st.values[moteus.Register.FAULT]
                print(f"id={i}  pos ={pos:.5f} Torque={tor:.5f}  phase current={cur:.5f} fault= {fault} ", end="  ")
            print()
            await asyncio.sleep(0.02)

    finally:
        # Always disarm both
        try:
            await asyncio.gather(*(ctl.set_stop() for ctl in c))
        except Exception:
            pass

if __name__ == '__main__':
    asyncio.run(main())