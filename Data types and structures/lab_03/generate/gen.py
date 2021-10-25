from random import *
import sys

c = int(sys.argv[1])
r = int(sys.argv[2])
d = int(sys.argv[3])

a = [0]*c*r

for i in range(round(c*r*d/100)):
    a[i] = randint(1, 9)

shuffle(a)

with open('..\\shared\\matrix.txt', 'w') as f:
    f.write(str(r) + " " + str(c) + "\n")
    for i in range(c):
        for j in range(r):
            f.write(str(a[r*i + j]) + (' ' if j < r - 1 else ''))
        f.write('\n')