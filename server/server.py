#!/usr/bin/env python3

import socket
import socketserver
import sys
import multiprocessing as mp
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
def parse_args(args):
	print(args)
	print("-v" in args)
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
	print(args)

	run_cosmos = args[0]
	run_visualizer = args[1]

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as csock, socket.socket(socket.AF_INET, socket.SOCK_STREAM) as vsock:

		# establish the COSMOS conneciton
		if run_cosmos:
			csock.bind(COSMOS_ADDRESS)
			print("Going to listen for COSMOS connection")
			csock.listen(0)
			print("Found COSMOS connection")
			c_conn, addr = csock.accept()
			print("Accept COSMOS connection")

		# establish the visualizer connection
		if run_visualizer:
			vsock.bind(VISUALIZER_ADDRESS)
			vsock.listen(1)
			v_conn, vaddr = vsock.accept()

		# continue with the connections
		if run_cosmos and run_visualizer:
			with c_conn, v_conn:
				print('Connected by', addr, 'and', vaddr)
				try:
					#the main loop -- figure out how much 
					while True:
						cdata = c_conn.recv(1024)
						v_conn.sendall(cdata)
						#vdata = v_conn.recv(1024)
						#if not cdata and not vdata: break
						if not cdata: 
							break
						else:
							print(cdata.hex())
						#if vdata:
						#	print("\t", vdata.hex())
						#print(cdata.hex(), "\n", vdata.hex())
						#c_conn.sendall(data)

				# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
				except KeyboardInterrupt:
					pass
				except ConnectionResetError: 
					print("\nConnection Ended")
		elif run_cosmos:
			with c_conn:
				print('Connected by', addr)
				try:
					#the main loop -- figure out how much 
					while True:
						rocket_data = teensy.read()
						#	break
						if not rocket_data: 
							c_conn.sendall('No Serial Data'.encode('UTF-8'))
						else:
							c_conn.sendall(rocket_data)
						command = c_conn.recv(1024) # receive commands
						print(command.hex())
						teensy.write(command)

				# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
				except KeyboardInterrupt:
					pass
				except ConnectionResetError: 
					print("\nConnection Ended")
	print("Exiting Server")

if __name__ == "__main__":
	#print(sys.argv[1:])
	args = parse_args(sys.argv[1:])
	#run_server(args)

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as csock:
		csock.bind(COSMOS_ADDRESS)
		print("Going to listen for COSMOS connection")
		csock.listen(0)
		print("Ltistened COSMOS connection")
		c_conn, addr = csock.accept()
		print("Accept COSMOS connection")