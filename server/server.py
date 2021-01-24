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
	retval = [False, False]
	if args == []:
		retval[0] = True
	else:
		if '-c' in args:
			retval[0] = True
		if '-v' in args:
			retval[1] = False
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

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as csock, socket.socket(socket.AF_INET, socket.SOCK_STREAM) as vsock:
		# establish the COSMOS conneciton
		csock.bind(COSMOS_ADDRESS)
		csock.listen(1)
		conn, addr = csock.accept()

		# establish the visualizer connection
		vsock.bind(VISUALIZER_ADDRESS)
		vsock.listen(1)
		vconn, vaddr = vsock.accept()

		# continue with the connections	
		with conn, vconn:
			print('Connected by', addr, 'and', vaddr)
			try:
				#the main loop -- figure out how much 
				while True:
					cdata = conn.recv(1024)
					vconn.sendall(cdata)
					#vdata = vconn.recv(1024)
					#if not cdata and not vdata: break
					if not cdata: 
						break
					else:
						print(cdata.hex())
					#if vdata:
					#	print("\t", vdata.hex())
					#print(cdata.hex(), "\n", vdata.hex())
					#conn.sendall(data)

			# allow the sockets to close naturally from the 'with' statments if the server is abruptly shutdown
			except KeyboardInterrupt: 
				pass
	print("\nExiting Server")

if __name__ == "__main__":
	#print(sys.argv[1:])
	args = parse_args(sys.argv[1:])
	run_server(args)