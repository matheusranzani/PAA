import numpy as np
import timeit
from matplotlib import pyplot as plt

def fatorial_itr(n):
    fat = 1
    for i in range(2, n + 1):
        fat = fat * i
    return(fat)

def fatorial_rec(n):
    if n == 0:
        return 1
    else:
        return n * fatorial_rec(n - 1)

n = 6

start_time = timeit.default_timer()
fatorial_itr(n)
print(timeit.default_timer() - start_time)

start_time = timeit.default_timer()
fatorial_rec(n)
print(timeit.default_timer() - start_time)