szam = raw_input("How many primes do you want?: ")
n = int(szam)
primek = [i for i in range(1,n)]
for j in range(2,n):
    for k in range(1,n):
        if k%j==0:
            if primek[j-1]!=0:
                print primek[j-1]
            primek[k-1]=0
