#!/usr/bin/env python3

import socket
import socketserver
import sys
#import multiprocessing as mp
from multiprocessing import Process, Queue
import threading
from hardware import device

teensy = device()
teensy.connect()

COSMOS_ADDRESS = ('127.0.0.1', 8888)
#COSMOS_ADDRESS = ('0.0.0.0', 8888)
VISUALIZER_ADDRESS = ('127.0.0.1', 1234)
'''
csock = socket.socket()
csock.connect((COSMOS_HOST, COSMOS_PORT))
VHOST, VPORT = '127.0.0.1', 0000
vsock = socket.socket()
vsock.connect((VHOST, VPORT))
'''

##################################################################
#                   	Helper Functions	                     #
##################################################################
'''
def visualizer_work(rocket_data):
	vsock.send(rocket_data)

def cosmos_work(rocket_data):
	csock.send(rocket_data)

def serial_listen():
	while True:
		pass
'''

def get_command(c_conn, command_queue, command_event):
	#put in job queue so it can be retrieved by the main process
	while not command_event.is_set():
		command = c_conn.recv(1024) # receive commands
		command_queue.put(command)

def parse_args(args):
	#print(args)
	#print("-v" in args)
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
#                   	Server Functions	                     #
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
			print("Going to listen for COSMOS connection")
			csock.listen(0)
			print("Found COSMOS connection")
			c_conn, addr = csock.accept()
			print("Accept COSMOS connection")
			command_queue = Queue()
			command_event = threading.Event()
			command_event.clear()
			cosmos_proc = Process(target=get_command, args=(c_conn, command_queue, command_event))

		# establish the visualizer connection
		if run_visualizer:
			vsock.bind(VISUALIZER_ADDRESS)
			vsock.listen(1)
			v_conn, vaddr = vsock.accept()

		# continue with the connections
		if run_cosmos and run_visualizer:
			print('Connected by', addr, 'and', vaddr)
			cosmos_proc.start()
			try:
				#the main loop -- figure out how much 
				while True:
					rocket_data = teensy.read()
					#print("Rocket data:", rocket_data)
					#	break
					#if not rocket_data: 
					#	c_conn.sendall('No Serial Data'.encode('UTF-8'))
					#else:
					#	c_conn.sendall(rocket_data)
					if rocket_data:
						print("Rocket data:", rocket_data)
						c_conn.sendall(rocket_data)
						v_conn.sendall(rocket_data)
					else:
						print("No rocket data")
					#command = c_conn.recv(1024) # receive commands
					#check job queue, send to rocket if there's anything
					if not command_queue.empty():
						command = command_queue.get()
						print("command.hex:", command.hex())
						teensy.write(command)

			# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
			except KeyboardInterrupt:
				pass
			except ConnectionResetError: 
				print("\nConnection Ended")
			finally: 
				command_event.set()
				cosmos_proc.join()
				# shutdown and accept no further sends or receives. shutdown allows close() to be completed quickly
				c_conn.shutdown(SHUT_RDWR) 
				c_conn.close()
				v_conn.shutdown(SHUT_RDWR)
				v_conn.close()
		elif run_cosmos:
			print('Connected by', addr)
			cosmos_proc.start()
			try:
				#the main loop -- figure out how much 
				while True:
					rocket_data = teensy.read()
					#print("Rocket data:", rocket_data)
					#	break
					#if not rocket_data: 
					#	c_conn.sendall('No Serial Data'.encode('UTF-8'))
					#else:
					#	c_conn.sendall(rocket_data)
					if rocket_data:
						print("Rocket data:", rocket_data)
						c_conn.sendall(rocket_data)
					else:
						print("No rocket data")
					#command = c_conn.recv(1024) # receive commands
					#check job queue, send to rocket if there's anything
					if not command_queue.empty():
						command = command_queue.get()
						print("command.hex:", command.hex())
						teensy.write(command)

			except KeyboardInterrupt:
				pass
			except ConnectionResetError: 
				print("\nConnection Ended")
			finally:
				command_event.set()
				cosmos_proc.join()
				c_conn.shutdown(SHUT_RDWR)
				c_conn.close()
		elif run_visualizer:
			print('Connected by', vaddr)
			try:
				#the main loop -- figure out how much 
				while True:
					rocket_data = teensy.read()
					#print("Rocket data:", rocket_data)
					#	break
					#if not rocket_data: 
					#	c_conn.sendall('No Serial Data'.encode('UTF-8'))
					#else:
					#	c_conn.sendall(rocket_data)
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
	#cosmos_proc.join()
	except KeyboardInterrupt:
		print()
	finally:
		csock.close()
		vsock.close()
		print("Exiting Server")

if __name__ == "__main__":
	#print(sys.argv[1:])
	args = parse_args(sys.argv[1:])
	run_server(args)

"""	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as csock:
		csock.bind(COSMOS_ADDRESS)
		print("Going to listen for COSMOS connection")
		csock.listen(0)
		print("Ltistened COSMOS connection")
		c_conn, addr = csock.accept()
		print("Accept COSMOS connection")
		while True:
			pass"""