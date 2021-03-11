#!/usr/bin/python3

import tkinter as tk
from hardware import device
import struct
import threading as th

dev_thread = None

cmd_q = []
cmd_q_mutex = th.Lock()

def int32(b):
    return int.from_bytes(b, byteorder='little') 

def fp32(b):
    return struct.unpack('f', b)[0]

def dev_handler(args):

    monitor = args[0]

    teensy = device()
    teensy.connect()
    fp = open("log.txt", "a")
    fp.write("==================== BEGIN LOG ====================\n")

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

        monitor.insert(tk.END, ln + '\n')
        fp.write(ln + '\n')

    cmd_q_mutex.acquire()
    if len(cmd_q) > 0:
        # todo proc command
        pass

    cmd_q_mutex.release()

def main():

    window = tk.Tk()
    monitor = tk.Text()
    cmdline = tk.Entry()
    sendbtn = tk.Button(text="Send")
    monitor.pack(expand=1, fill=tk.BOTH)
    cmdline.pack(expand=1, side=tk.LEFT, fill=tk.X)
    sendbtn.pack(side=tk.RIGHT)

    dev_thread = th.Thread(target=dev_handler, args=(monitor,))
    dev_thread.start()
    
    window.mainloop()

if __name__ == "__main__":
    main()
