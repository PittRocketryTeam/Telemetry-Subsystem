#!/usr/bin/env python3

import serial
import serial.tools.list_ports

class device:

	ser = None

	def __init__(self):
		self.ser = serial.Serial()

	# delete and close port
	def __del__(self):
		self.ser.__del__()

	# returns true if comm channel is open, false if closed 
	def is_connected(self):
		return self.ser.is_open()

	# connects to connected mcu
	def connect(self, name="USB"):
		port = self.get_MCU_port(name)
		if port != "NONE":
			self.ser.port = port
			self.ser.timeout = 0
			self.set_baud_rate(9600)
			self.ser.open()
			print("MCU Connected")
		else:
			print("Connection Error -- No MCU Connected")

	# return a list of communication ports
	def get_ports(self):
		return serial.tools.list_ports.comports()

	# get the port connected to the MCU
	def get_MCU_port(self, name):
		ports = self.get_ports()
		ret = "NONE"
		for port in ports:
			port = str(port)
			if port.find(name) != -1:
				#ret = port.split(' ')[0]
				ret = port.strip()
				ret = ret[ret.find("\'")+1:ret.find("\'", 3)]
		return ret

	# sets baud rate for serial connection
	def set_baud_rate(self, rate):
		self.ser.baudrate = rate

	# returns baud rate of serial connection
	def get_baud_rate(self):
		if self.is_connected():
			return self.ser.baudrate
		else:
			print("Could not set baud rate -- serial not connected")
			return 0

	# return the contents in the serial input queue
	def read(self):
		if self.is_connected():
			num_available_bytes = self.ser.inWaiting()
			return self.ser.read(num_available_bytes)
		else:
			print("Serial port not open")
			return 0

	# write the data out to the serial port
	def write(self, data):
		'''
		see if theres a connection, if the port is writeable, 
		then if the data type is bytes to optimize conversion
		'''
		if self.is_connected():
			if self.ser.writable():
				try:
					if type(data) is bytes:
						return self.ser.write(data)
					else:
						return self.ser.write(str(data).encode('UTF-8'))
				except Exception as e:
					print("Could not write data to serial -- ", e)
					return 0
			else:
				print("Serial port not writable")
				return 0
		else:
			print("Serial port not open")
			return 0