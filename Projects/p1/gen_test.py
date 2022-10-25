import random

N = int(random.expovariate(10**-4))

i = 0

print(N)
while (i<N):
    x = int(random.gammavariate(0.5,0.5)*N)
    y = int(random.gammavariate(0.5,0.5)*N)
    print(str(x)+" "+str(y))
    i = i+1


