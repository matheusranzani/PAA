import numpy as np
import timeit
from matplotlib import pyplot as plt

dt_c = []
memo = {}
def fatorial_rec_memoization(n):
    if n in memo:
        return memo[n]
    elif n == 0:
        return 1
    else:
        x = fatorial_rec_memoization(n-1) * n
        memo[n] = x
        return x

dt_a = []
def fatorial_itr(n):
    fat = 1
    for i in range(1, n + 1):
        fat = fat * i
    return(fat)

dt_b = []
def fatorial_rec(n):
    if n == 0:
        return 1
    else:
        return n * fatorial_rec(n - 1)

r = range(1, 100)
start_time = timeit.default_timer()
for n in r: 
    fatorial_rec(n)
    dt_b.append(timeit.default_timer() - start_time)

r = range(1, 100)
start_time = timeit.default_timer()
for n in r: 
    fatorial_rec_memoization(n)
    dt_c.append(timeit.default_timer() - start_time)

r = range(1, 100)
start_time = timeit.default_timer()
for n in r: 
    fatorial_itr(n)
    dt_a.append(timeit.default_timer() - start_time)

plt.plot(r, dt_a, color="red", label="iteration ")
plt.plot(r, dt_b, color="blue", label="recursion")
plt.plot(r, dt_c, color="black", label="recursion + memoization")
plt.legend(loc="upper left")
plt.ylabel("Time(x)")
plt.xlabel("Size")
plt.show()