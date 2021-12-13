from random import *
import sys

count_elems = int(sys.argv[1])
filename = sys.argv[2]

a = [0] * count_elems

for i in range(count_elems):
    a[i] = randint(-count_elems, count_elems)

shuffle(a)

with open(filename, 'w') as f:
    for j in range(count_elems):
        f.write(str(a[j]) + ' ')