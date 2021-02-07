import socket
import time
import sys

SERVER = ('127.0.0.1', 8888)
VSERVER = ('127.0.0.1', 1234)

args = sys.argv[1:]
retval = [False, False]
if args == []:
	retval[0] = True
else:
	if "-c" in args:
		retval[0] = True
	if "-v" in args:
		retval[1] = True

if retval[0]:
	csock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # this line must contain these arguments or it fails!
	csock.connect(SERVER)
time.sleep(0.5) # must be added so server has time to accept the connection
if retval[1]:
	vsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	vsock.connect(VSERVER)
count = 0

packet = bytearray.fromhex("00100004001600AA00BB")

count += 1
#csock.sendto(packet, ('127.0.0.1', 8888))
#csock.connect((HOST, PORT))
try:
	data = bytearray.fromhex("00100004001600AA00BB")
	while True:
		if retval[0]:
			cdata = csock.recv(1024)
			csock.sendall(data)
		if retval[1]:
			vdata = vsock.recv(1024)
			#vsock.sendall(b'Hello Maje')
			print("\t", vdata.hex())
		#print("Sent")
		time.sleep(1)
except KeyboardInterrupt:
	if retval[0]:
		csock.close()
	if retval[1]:
		vsock.close()

'''
for payload in payloads:
    count += 1
    csock.sendto(payload, SERVER)
    time.sleep(0.001)
'''