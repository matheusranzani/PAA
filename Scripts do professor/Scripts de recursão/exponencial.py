def exponencial(x,n):
    if n == 0:
        return 1
    else:
        return x * exponencial(x, n - 1)

print(exponencial(7, 13))