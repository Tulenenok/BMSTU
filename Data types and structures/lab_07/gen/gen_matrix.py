from random import *
import sys

c = int(sys.argv[1])
r = int(sys.argv[2])

a = [0]*c*r

for i in range(c*r):
    a[i] = randint(0, 100)

shuffle(a)

with open(f'..\\data\\graph_{c}.txt', 'w') as f:
    f.write(str(r) + " " + str(c) + "\n")
    for i in range(c):
        for j in range(r):
            f.write(str(a[r*i + j]) + (' ' if j < r - 1 else ''))
        f.write('\n')