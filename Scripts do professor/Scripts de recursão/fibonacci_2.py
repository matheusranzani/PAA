import sys
import functools
import numpy as np
import timeit
from matplotlib import pyplot as plt

sys.setrecursionlimit(10500)

dt_a = []
def fibonacci_loop(n):
    if n in {0, 1}:
        return n
    fn_2 = 0
    fn_1 = 1
    for i in range(2, n + 1):
        fn = fn_1 + fn_2
        fn_2 = fn_1
        fn_1 = fn
    return fn

dt_b = []
memoization = {0: 0, 1: 1}
def fibonacci_rec_memoization(n):
    if n in memoization:
        return memoization[n]
    memoization[n] = fibonacci_rec_memoization(n - 1) + fibonacci_rec_memoization(n - 2) 
    return memoization[n]

r = range(1, 200)

start_time = timeit.default_timer()
for n in r: 
    fibonacci_loop(n)
    dt_a.append(timeit.default_timer() - start_time)

start_time = timeit.default_timer()
for n in r: 
    fibonacci_rec_memoization(n)
    dt_b.append(timeit.default_timer() - start_time)

plt.plot(r, dt_a, color="red", label="iteration")
plt.plot(r, dt_b, color="blue", label="recursion + memoization")
plt.legend(loc="upper left")
plt.ylabel("Time(x)")
plt.xlabel("Size")
plt.show()