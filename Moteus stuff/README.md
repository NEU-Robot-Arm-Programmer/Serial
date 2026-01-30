This folder contains python scripts to interface with the moteus drivers 
- Each joint will be a seperately addressable driver which can be commanded over CAN
- the "mjcanfd-usb-1x" device is a small microcontroller board which takes usb inputs and creates necessary CAN commands to send to the bus of daisy-chained moteus drivers (we have one of these devices, need to install the moteus python library before use)
- Each driver has a unique UUID, this is the most reliable way to address them
- To get the UUIDs and info about the connected drivers, run this in the command prompt window "python -m moteus.moteus_tool --query"
