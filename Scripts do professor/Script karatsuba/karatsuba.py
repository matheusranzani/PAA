import math

def number_of_digits(number):
    """
    Used log10 to find no. of digits
    """

    if number > 0:
        return int(math.log10(number)) + 1
    elif number == 0:
        return 1
    else:
        return int(math.log10(-number)) + 1

def karatsuba(x, y):
    """
    Karatsuba algorithm for fast multiplication
    """

    if x < 10 or y < 10:
        return x * y
    else:
        m = max(number_of_digits(x), number_of_digits(y))
        m2 = m // 2

        xl = x // 10 ** (m2)
        xr = x % 10 ** (m2)
        yl = y // 10 ** (m2)
        yr = y % 10 ** (m2)

        z0 = karatsuba(xr, yr)
        z1 = karatsuba((xl + xr), (yl + yr))
        z2 = karatsuba(xl, yl)

        return (z2 * 10 ** (2 * m2)) + ((z1 - z2 - z0) * 10 ** (m2)) + (z0)

print(karatsuba(5678, 1234))
print(karatsuba(857129, 428937))