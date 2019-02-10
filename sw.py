from time import sleep
from threading import Thread
from msvcrt import getch
import datetime

stop_flag = True
end_flag = False

hour = minute = second = 0
mode = 0
NUM = 2

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
    global NUM, stop_flag, hour, minute, second
    print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="              ")
    while True:
        if not stop_flag:
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="              ")
            sleep(1)
            hour, minute, second = sec_add(hour, minute, second)

def clock():
    global NUM
    while True:
        print("\r"+datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S"), end="              ")

def key_input():
    global NUM, mode, stop_flag, end_flag, hour, minute, second
    while True:
        key = ord(getch())
        if key == 115 and mode == 0 % NUM:
            stop_flag = not(stop_flag) 
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="              ")
        elif key == 114 and mode == 0 % NUM:
            hour = minute = second = 0
            stop_flag = True 
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="              ")
        elif key == 108 and mode == 0 % NUM:
            print("\rLAP:"+"{:02d}:{:02d}'{:02d}".format(hour, minute, second))
            print("\r{:02d}:{:02d}'{:02d}".format(hour, minute, second), end="              ")
        elif key == 109:
            mode += 1
            #print("\r", end="              ")
            #print("\rmode={}".format(mode%2), end="              ")
        elif key == 101:
            end_flag = True
            break

def run():
    global NUM, mode, end_flag
    while True:
        #print("\rmode={}".format(mode%2), end="              ")
        if mode == 0 % NUM:
            timer()
        elif mode == 1 % NUM:
            clock()
        if end_flag:
            break
if __name__ == "__main__":
    print("s:start,stop  r:reset  l:lap  m:mode change  e:exit")
    thread1 = Thread(target=run)
    thread2 = Thread(target=key_input)
    thread1.start()
    thread2.start()
