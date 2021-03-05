#!/usr/bin/env python3

import socket
import socketserver
import sys
from multiprocessing import Process, Queue
import threading
from hardware import device

COSMOS_ADDRESS = ('127.0.0.1', 8888)
VISUALIZER_ADDRESS = ('127.0.0.1', 1234)

'''
## IMPORTANT COMMENT:

MAKE SURE THAT YOU LEAVE TIME BETWEEEN CONNECTING COSMOS THEN VISUALIZER!
The system needs time to setup the connection or something
'''

##################################################################
#                   	Helper Functions	                     #
##################################################################

def get_command(c_conn, command_queue, command_event):
	'''Read COSMOS to see it has sent any commands and put them in the job queue 
	so they can be retrieved by the main process and sent to the rocket'''

	while not command_event.is_set():
		command = c_conn.recv(1024) # receive commands
		command_queue.put(command)


def parse_args(args):
	'''Parse the commandline arguments to see which programs to read from 
	and return the list of those boolean vals to the main method

	COSMOS is represented as first in the list, the visualizer is second''' 

	retval = [False, False]
	if args == []:
		retval[0] = True
	else:
		if "-c" in args:
			retval[0] = True
		if "-v" in args:
			retval[1] = True
	return retval

##################################################################
#                      Server Functionality                      #
##################################################################

def run_server(args):
	''' 
	Creates a socket and a bound to COSMOS first, then the visualizer
		There must be a delay on the client end between the COSMOS thread and the visualizer thread
		to allow the server to establish the COSMOS socket before the visualizer connection can
		be processed

	'''
	print("Server Starting")
	print("args:", args)

	run_cosmos = args[0]
	run_visualizer = args[1]

	#with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as csock, socket.socket(socket.AF_INET, socket.SOCK_STREAM) as vsock:

	try:
		csock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		vsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		
		# establish the COSMOS conneciton
		if run_cosmos:
			csock.bind(COSMOS_ADDRESS)
			#print("Going to listen for COSMOS connection")
			csock.listen(0)
			#print("Found COSMOS connection")
			c_conn, addr = csock.accept()
			print("Accepted COSMOS connection")

			# setup the COSMOS job queue checking process to asynchronously notify the main process when a command is available to be sent
			command_queue = Queue()
			# setup condvar type thing used to trigger the queu-checking process to stop execution so the process can be terminated
			command_event = threading.Event()
			command_event.clear() # setting event to false
			# have a subprocess just try and receive commands from COSMOS and once they're received the're put in the job queue
			cosmos_proc = Process(target=get_command, args=(c_conn, command_queue, command_event))

		# establish the visualizer connection
		if run_visualizer:
			vsock.bind(VISUALIZER_ADDRESS)
			vsock.listen(1)
			v_conn, vaddr = vsock.accept()
			print("Accepted visualizer connection")


		if run_cosmos and run_visualizer: # send data to both the visualizer and COSMOS and send any COSMOS commands received by the other process
			print('Connected by', addr, 'and', vaddr)
			cosmos_proc.start()
			try:
				#the main loop
				while True:
					rocket_data = teensy.read()

					if rocket_data:
						print("Rocket data:", rocket_data)
						c_conn.sendall(rocket_data)
						v_conn.sendall(rocket_data)
					else:
						print("No rocket data")
					#command = c_conn.recv(1024) # receive commands

					# read command queue from COSMOS, send to rocket if there's anything
					if not command_queue.empty():
						command = command_queue.get()
						print("Command.hex from COSMOS:", command.hex())
						teensy.write(command)

			# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
			except KeyboardInterrupt:
				pass
			except ConnectionResetError: 
				print("\nConnection Ended")
			finally: 
				command_event.set() # tell the queue-checking loop to terminate
				cosmos_proc.join()
				# shutdown and accept no further sends or receives. shutdown allows close() to be completed quickly
				c_conn.shutdown(SHUT_RDWR) 
				c_conn.close()
				v_conn.shutdown(SHUT_RDWR)
				v_conn.close()
		
		elif run_cosmos: # only send rocket data to COSMOS and relay commands from COSMOS to the rocket
			print('Connected by', addr)
			cosmos_proc.start()
			try:
				while True:
					rocket_data = teensy.read()

					if rocket_data:
						print("Rocket data:", rocket_data)
						c_conn.sendall(rocket_data)
					else:
						print("No rocket data")
					#command = c_conn.recv(1024) # receive commands
					
					# read command queue from COSMOS, send to rocket if there's anything
					if not command_queue.empty():
						command = command_queue.get()
						print("Command.hex from COSMOS:", command.hex())
						teensy.write(command)

			except KeyboardInterrupt:
				pass
			except ConnectionResetError: 
				print("\nConnection Ended")
			finally:
				command_event.set() # tell the queue-checking loop to terminate
				cosmos_proc.join()
				# shutdown and accept no further sends or receives. shutdown allows close() to be completed quickly
				c_conn.shutdown(SHUT_RDWR)
				c_conn.close()

		elif run_visualizer: # only send rocket data to the visualizer 
			print('Connected by', vaddr)
			try:
				#the main loop
				while True:
					rocket_data = teensy.read()

					if rocket_data:
						print("Rocket data:", rocket_data)
						v_conn.sendall(rocket_data)
					else:
						print("No rocket data")

			# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
			except KeyboardInterrupt:
				pass
			except ConnectionResetError: 
				print("\nConnection Ended")
			finally:
				# shutdown and accept no further sends or receives. shutdown allows close() to be completed quickly
				v_conn.shutdown(SHUT_RDWR)
				v_conn.close()

	except KeyboardInterrupt:
		print()
	finally:
		csock.close()
		vsock.close()
		print("Exiting Server")

if __name__ == "__main__":
	# connect to the teensy, device() from hardawre file
	teensy = device()
	teensy.connect()

	# parse the given program arguments and run the server
	args = parse_args(sys.argv[1:])
	run_server(args)
