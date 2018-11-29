import random
import sys

capital = 1000000
win_per = 0.5
bet = 1000

for i in range(10000):
    rnd = random.randint(1, 100)
    if capital < 1000:
        break
    bet = 1000
    if rnd < 100*win_per:
        flag = "Win"
        capital += bet*0.85
    else:
        flag = "Lose"
        capital -= bet
    print("i={:6d} : {:4s} {:6d}".format(i+1, flag, int(capital)))
    #if (i+1) % 100 == 0:
        #print("i={:6d}:{}".format(i+1, int(capital)))
        #sys.stdout.write("\ri={}:{}".format(i+1, int(capital)))
        #sys.stdout.flush()
