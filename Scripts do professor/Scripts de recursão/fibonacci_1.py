import sys
import functools
import numpy as np
import time
from matplotlib import pyplot as plt

sys.setrecursionlimit(10500)
print("Recursion Limit:", sys.getrecursionlimit(), "\n")

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

def fibonacci_rec(n):
    if n in {0, 1}:
        return n
    else:
        return fibonacci_rec(n - 1) + fibonacci_rec(n - 2)

memoization = {0: 0, 1: 1}
def fibonacci_rec_memoization(n):
    if n in memoization:
        return memoization[n]
    memoization[n] = fibonacci_rec_memoization(n - 1) + fibonacci_rec_memoization(n - 2) 
    return memoization[n]

@functools.lru_cache(maxsize=None) #128 by default
def fibonacci_rec_functools(n):
    if n in {0, 1}:
        return n
    else:
        return fibonacci_rec_functools(n - 1) + fibonacci_rec_functools(n - 2)

print("Fibonacci sequence")
for i in range(0, 11):
    print(i, ":", fibonacci_loop(i))

n = 7

print("\nFibonacci with for")
print(fibonacci_loop(n))

print("\nFibonacci with recursion")
print(fibonacci_rec(n))

print("\nFibonacci with recursion and memoization")
print(fibonacci_rec_memoization(n))

print("\nFibonacci with recursion and functools")
print(fibonacci_rec_memoization(n))