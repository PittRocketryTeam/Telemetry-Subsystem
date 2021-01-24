import socket
import time

SERVER = ('127.0.0.1', 8888)
HOST, PORT = '127.0.0.1', 8888

sock = socket.socket()
count = 0

packet = bytearray.fromhex("00100004001600AA00BB")

count += 1
#sock.sendto(packet, ('127.0.0.1', 8888))
#sock.connect((HOST, PORT))
while True:
	sock.sendto(bytearray.fromhex("00100004001600AA00BB"), (HOST, PORT))
	time.sleep(1)

'''
for payload in payloads:
    count += 1
    sock.sendto(payload, SERVER)
    time.sleep(0.001)
'''
sock.close()
