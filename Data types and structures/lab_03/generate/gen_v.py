from random import *
import sys

r = int(sys.argv[1])
d = int(sys.argv[2])

a = [0]*r

for i in range(round(r*d/100)):
    a[i] = randint(1, 9)

shuffle(a)

with open('..\\shared\\vector.txt', 'w') as f:
    f.write(str(r) + " 1\n")
    for j in range(r):
        f.write(str(a[j]) + ('\n' if j < r - 1 else ''))
    f.write('\n')