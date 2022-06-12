from random import randint, seed
from sys import argv

argc = len(argv)
if argc != 4:
    print(f"Usage: {argv[0]} rows cols n")
    exit(1)

rows = int(argv[1])
cols = int(argv[2])
n = int(argv[3])
seed(1)

print(n)
for _ in range(n):
    x = randint(1, rows)
    y = randint(1, cols)
    print(x, y)
