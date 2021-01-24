import socket
import time

SERVER = ('127.0.0.1', 8888)
VSERVER = ('127.0.0.1', 1234)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # this line must contain these arguments or it fails!
sock.connect(SERVER)
time.sleep(0.5) # must be added so server has time to accept the connection
vsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
vsock.connect(VSERVER)
count = 0

packet = bytearray.fromhex("00100004001600AA00BB")

count += 1
#sock.sendto(packet, ('127.0.0.1', 8888))
#sock.connect((HOST, PORT))
while True:
	data = bytearray.fromhex("00100004001600AA00BB")
	sock.sendall(data)
	#vsock.sendall(b'Hello Maje')
	vdata = vsock.recv(1024)
	#print("Sent")
	print(vdata.hex())
	time.sleep(1)

'''
for payload in payloads:
    count += 1
    sock.sendto(payload, SERVER)
    time.sleep(0.001)
'''
sock.close()
