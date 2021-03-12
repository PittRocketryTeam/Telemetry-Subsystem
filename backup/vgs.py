#!/usr/bin/python3

import tkinter as tk
from hardware import device
import threading as th
from vehicle import State
import time

dev_thread = None
window = None
monitor = None
cmdline = None

running = True

cmd_q = []
cmd_q_mutex = th.Lock()

def send_cb(event):
    cmd_q_mutex.acquire()
    cmd_q.append(cmdline.get())
    cmd_q_mutex.release()
    cmdline.delete(0, "end")

def shutdown():
    global window
    global running
    global dev_thread

    running = False
    print("waiting on worker...")
    if dev_thread:
        dev_thread.join()
    window.destroy()

def dev_handler(monitor):
    global running

    st = State()

    teensy = device()
    teensy.connect()
    fp = open("log.txt", "a")
    fp.write("==================== BEGIN LOG ====================\n")
    while running:
        
        data = (teensy.read())
        st.extract(data)

        # todo parse

        if st.update:
            ln = st.getline()
            monitor.configure(state=tk.NORMAL)
            monitor.insert(tk.END, ln + '\n')
            fp.write(ln + '\n')
            monitor.configure(state=tk.DISABLED)
            monitor.see("end")

        cmd_q_mutex.acquire()
        if len(cmd_q) > 0:
            monitor.configure(state=tk.NORMAL)
            monitor.insert(tk.END, "SEND COMMAND: " + cmd_q[0] + '\n')
            monitor.configure(state=tk.DISABLED)
            cmd_q.pop(0)
            monitor.see("end")

        cmd_q_mutex.release()

        #time.sleep(0.001)

def main():
    global window
    global monitor
    global cmdline
    global dev_thread

    window = tk.Tk()
    window.protocol("WM_DELETE_WINDOW", shutdown)
    monitor = tk.Text(state=tk.DISABLED)
    cmdline = tk.Entry()
    cmdline.bind("<Return>", send_cb)
    sendbtn = tk.Button(text="Send")
    sendbtn.bind("<ButtonRelease-1>", send_cb)

    monitor.pack(expand=1, fill=tk.BOTH)
    cmdline.pack(expand=1, side=tk.LEFT, fill=tk.X)
    sendbtn.pack(side=tk.RIGHT)    

    dev_thread = th.Thread(target=dev_handler, args=(monitor,))
    dev_thread.start()
    
    window.mainloop()

if __name__ == "__main__":
    main()
