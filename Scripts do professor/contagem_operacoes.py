def algorithm(n):
    for i in range(0, n):
        print("i:", i)
        for j in range(i+1, n):
            print("\tj:", j)
            for k in range(1, (j - i)+1):
                print("\t\tk:", k)

n = 10
algorithm(n)

def algorithm(n):
    print("\ni[", 0, "...", n-1, "]")
    for i in range(0, n):
        print("i:", i)
        print("\tj[", i+1, "...", n-1, "]")
        for j in range(i+1, n):
            print("\t\tk[", 1, "...", (j - i), "]")

n = 10
algorithm(n)
