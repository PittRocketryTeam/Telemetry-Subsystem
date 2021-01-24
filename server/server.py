#!/usr/bin/env python3

import socket
import socketserver
import multiprocessing as mp
import threading
from hardware import device

teensy = device()
teensy.connect()

CHOST, CPORT = '127.0.0.1', 8888
'''
csock = socket.socket()
csock.connect((CHOST, CPORT))
VHOST, VPORT = '127.0.0.1', 0000
vsock = socket.socket()
vsock.connect((VHOST, VPORT))
'''

##################################################################
#                   	Server Functions	                     #
##################################################################
'''
def visualizer_work(rocket_data):
	vsock.send(rocket_data)

def cosmos_work(rocket_data):
	csock.send(rocket_data)
'''

def serial_listen():
	while True:
		pass

##################################################################
#                   	Server Functions	                     #
##################################################################

class MyTCPHandler(socketserver.BaseRequestHandler):

	def handle(self):
		print(self.request.recv(1024).hex())

def run_server():
	print("Server Starting")

	serial_thread = threading.Thread(target=serial_listen(), daemon=True)
	serial_thread.start()

	with socketserver.TCPServer((CHOST, CPORT), MyTCPHandler) as server:
		try:
			server.serve_forever()
		except KeyboardInterrupt:
			print("\nServer Terminating")

if __name__ == "__main__":
	run_server()