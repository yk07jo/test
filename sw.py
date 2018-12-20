from time import sleep
from threading import Thread
from msvcrt import getch
import sys

stop_flag = False
end_flag = False

hour = minute = second = 0

def sec_add(hour, minute, second):
    second += 1
    if second == 60:
        minute += 1
        second = 0
    if minute == 60:
        hour += 1
        minute = 0
    return hour, minute, second

def timer():
    global stop_flag, end_flag, hour, minute, second
    while True:
        if not stop_flag:
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="")
            sleep(1)
            hour, minute, second = sec_add(hour, minute, second)
        if end_flag:
            break
def key_input():
    global stop_flag, end_flag, hour, minute, second
    while True:
        key = ord(getch())
        if key == 115:
            stop_flag = not(stop_flag) 
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="")
        elif key == 114:
            hour = minute = second = 0
            stop_flag = True 
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="")
        elif key == 108:
            print("\rLAP:"+"{:02d}:{:02d}'{:02d}".format(hour, minute, second))
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="")
        elif key == 101:
            end_flag = True
            break

print("s:start,stop  r:reset  l:lap  e:exit")
thread1 = Thread(target=timer)
thread2 = Thread(target=key_input)
thread1.start()
thread2.start()
