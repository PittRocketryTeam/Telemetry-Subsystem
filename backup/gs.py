#!/usr/bin/python3

from hardware import device
import struct

teensy = device()
teensy.connect()

def int32(b):
    return int.from_bytes(b, byteorder='little') 

def fp32(b):
    return struct.unpack('f', b)[0]

fp = open("log.txt", "a")
fp.write("==================== BEGIN LOG ====================\n")
print("Len\tID\tAx\tAy\tAz\tWx\tWy\tWz\tLat\t\tLon\t\tAlt")
while True:
    data = (teensy.read())
    #if len(data) > 4: print(data)

    if data and len(data) == 62:
        pln = int32(data[0:4])
        pid = int32(data[4:8])
        ax = fp32(data[8:12])
        ay = fp32(data[12:16])
        az = fp32(data[16:20])
        wx = fp32(data[20:24])
        wy = fp32(data[24:28])
        wz = fp32(data[28:32])
        qx = fp32(data[32:36])
        qy = fp32(data[36:40])
        qz = fp32(data[40:44])
        qw = fp32(data[44:48])
        lat = fp32(data[48:52])
        lon = fp32(data[52:56])
        alt = fp32(data[56:60])

        ln = '{0}\t{1}\t{2:.3f}\t{3:.3f}\t{4:.3f}\t{5:.3f}\t{6:.3f}\t{7:.3f}\t{8:.3f}\t{9:.3f}\t{10:.3f}'.format(
            pln,
            pid,
            ax,
            ay,
            az,
            wx,
            wy,
            wz,
            lat,
            lon,
            alt
        )

        print(ln, '\r', end='')
        fp.write(ln + '\n')
