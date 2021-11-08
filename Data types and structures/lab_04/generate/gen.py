import sys

count_elems = int(sys.argv[1])

with open('..\\shared\\stack.txt', 'w') as f:
    f.write(str(count_elems) + "\n")
    f.write("a" * count_elems + "\n")