#!/usr/bin/python3

import struct

def int32(b):
    return int.from_bytes(b, byteorder='little') 

def fp32(b):
    return struct.unpack('f', b)[0]

class State:
    def __init__(self):
        self.len = 0
        self.id = 0
        self.temp = 0
        self.vbat = 0
        self.ibat = 0
        self.tbat = 0
        self.pres = 0
        self.alt = 0
        self.nsats = 0
        self.lat = 0
        self.lon = 0
        self.ax = 0
        self.ay = 0
        self.az = 0
        self.wx = 0
        self.wy = 0
        self.wz = 0

        self.update = False
        self.line = ""

    def extract(self, data):
        if data and (len(data) == 62 or len(data) == 30):
            self.update = True
            pln = int32(data[0:4])
            pid = int32(data[4:8])

            if pid == 5: # orientation
                self.ax = fp32(data[8:12])
                self.ay = fp32(data[12:16])
                self.az = fp32(data[16:20])
                self.wx = fp32(data[20:24])
                self.wy = fp32(data[24:28])
                self.wz = fp32(data[28:32])
                self.qx = fp32(data[32:36])
                self.qy = fp32(data[36:40])
                self.qz = fp32(data[40:44])
                self.qw = fp32(data[44:48])
                self.lat = fp32(data[48:52])
                self.lon = fp32(data[52:56])
                self.alt = fp32(data[56:60])

            elif pid == 4: # health
                self.vbat = fp32(data[8:12])
                self.ibat = fp32(data[12:16])
                self.tbat = fp32(data[16:20])
                self.temp = fp32(data[20:24])
                self.nsats = int32(data[24:28])

    def getline(self):
        if not self.update:
            return ""

        self.update = False
        return '{0:.3f}\t{1:.3f}\t{2:.3f}\t{3:.3f}\t{4:.3f}\t{5:.3f}\t{6:.3f}\t{7:.3f}\t{8:.3f}\t{9:.3f}\t{10:.3f}\t{11:.3f}\t{12:.3f}'.format(
                self.ax,
                self.ay,
                self.az,
                self.wx,
                self.wy,
                self.wz,
                self.lat,
                self.lon,
                self.alt,
                self.nsats,
                self.vbat,
                self.ibat,
                self.tbat,
                self.temp
            )