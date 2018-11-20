import random

capital = 100000
win_per = 0.55
bet = 1000

for i in range(365):
    rnd = random.randint(1, 100)
    if capital < bet:
        break
    if rnd < 100*win_per:
        flag = "Win"
        capital += bet*0.85
    else:
        flag = "Lose"
        capital -= bet
    print("i={:3d}:{:4s} {}".format(i+1, flag, int(capital)))
