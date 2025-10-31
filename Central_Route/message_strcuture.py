import asyncio
from dataclasses import dataclass, asdict
import json
import logging
import threading
import time
from typing import Any, Dict
import itertools

"""
message_structure.py
------------------
A safe, non-blocking communication architecture for multiple robot devices using:
- Threads for each blocking device I/O (e.g., camera, serial)
- An asyncio "message bus" for passing messages between components
- Latency logging to measure end-to-end timing

Key concepts:
-------------
publish(topic, msg): send a message to all boards interested in that topic.
subscribe(topic): receive messages for that topic through an async queue.

Example topics:
    "hand_coords"  -> coordinates from the camera hand tracker
    "telemetry"    -> sensor or Teensy data
    "commands"     -> high-level robot commands

Everything uses a consistent message format defined by the Message dataclass.
"""

logging.basicConfig(level=logging.INFO, format='[%(asctime)s] %(message)s')
_seq = itertools.count()

@dataclass
class Message:
	"""
	Will be the standard message structure
	"""
	source: str						# where this message came from (e.g. "camera", "teensy_hand")
	type: str						# the topic/category (e.g. "hand_coords", "telemetry")
	seq: int       					# Number for debugging
	ts_created: float				# time the message was created
	payload: Dict[str, Any]			# contain the actual data, ex: {"x":1.0, "y":1.4, "z":2.5} in meters ->
	coords: Dict[str, float]

	def to_json(self):
		return json.dumps(asdict(self))

	def mark_processed(self):
		self.ts_created = time.time()

	def latency_ms(self, processed_time=None):
		"""Compute how many milliseconds have passed since the message was created."""
		processed_time = processed_time or time.time()
		return (processed_time - self.ts_created) * 1000

class MessageBus:
	"""
	Think of this as a Transmit/Listen router.

	- Devices (in threads) call transmit() to send messages.
    - Consumers (async tasks) call dial_in() to receive messages.
    - Each topic (string) has its own set of queues for subscribers.
    """
	def __init__(self):
		# topic -> list of asyncio.Queue (one per subscriber)
		self.listeners = {}
		# the lock here is to be thread safe access when modifying the list of listeners
		self.lock = asyncio.Lock()

	async def transmit(self, topic: str, maxsize=50) -> asyncio.Queue:
		"""
		Transmit a topic.

		:param topic:
		:type topic: string
		:param maxsize:
		:type maxsize: integer
		:return: A queue that will receive messages for topic.
		:rtype: asyncio.Queue
		"""
		q = asyncio.Queue(maxsize=maxsize)
		async with self.lock:
			self.listeners.setdefault(topic, []).append(q)
		logging.info(f"[MessageBus] New listener fro topic {topic}")
		return q

	async def publish(self, topic:str, msg:Message, drop_oldest=True):
		"""
		Publish a message to all listeners
		:param topic:
		:type topic: string
		:param msg:
		:type msg: Message
		:param drop_oldest:
		:type drop_oldest: boolean
		:return:
		:rtype:
		"""
		async with self.lock:
			queues = self.listeners.get(topic, [])
		for q in queues:
			try:
				q.put_nowait(msg)
			except asyncio.QueueFull:
				if drop_oldest:
					# drop the oldest message to make more space
					try:
						_ = q.get_nowait()
						q.task_done()
						q.put_nowait(msg)
					except asyncio.QueueFull:
						logging.warning(f"[MessageBus] Dropped message {msg.seq} on '{topic}' (queue full)")
				else:
					# block until space in the queue frees up
					await q.put(msg)


########################################################
#                                                      #
#                Device Handler                        #
#         runs each device on its own thread           #
########################################################
import asyncio
import threading


class DeviceHandler:
	"""
	This file will represent one hardware interface (such as the camera, teensy, or the glove, etc.)
	Each device runs in its own thread, reads, or generates data and sends it to a central message bus.

	This should keep the I/O from freezing the main event loop.
	"""

	def __init__(self, name: str, loop: asyncio.AbstractEventLoop, publish_func, device_id: str):
		self.device_id = device_id
		self.loop = loop
		self.publish = publish_func
		self.running = threading.Event()
		self.thread = None

	def start(self):
		"""
		Start the device through a background thread.
		:return:
		:rtype:
		"""
		self.running.set()
		self.thread = threading.Thread(target=self._thread_loop, daemon=True)
		self.thread.start()
		# i think the logging needs to be in the message struc mod
		logging.info(f"[DeviceHandler] {self.device_id} thread started.")

	def stop(self):
		"""
		Stop the background thread.
		:return:
		:rtype:
		"""
		self.running.clear()
		if self.thread:
			self.thread.join()

	def _thread_loop(self):
		"""
		Simulated device loop. Replace this with actual I/O device
		:return:
		:rtype:
		"""
		while self.running.is_set():
			# create a fake message to simulate data
			msg = Message(source=self.device_id,
						  type="hand_cords" if "camera" in self.device_id else "telemetry",
						  seq=next(_seq),
						  ts_created=time.time(),
						  payload={{"x": 1.0, "y": 2.0, "z": 3.0}}
			)

			# launch a thread safe way to tell teh async loop to transmit this message
			self.loop.call_soon_threadsafe(
				asyncio.create_task, self.publish(msg=msg)
			)

			# try a 20Hz rate (so ~50ms per cycle)
			time.sleep(0.05)

		logging.info(f"[DeviceHandler] {self.device_id} thread stopped.")

