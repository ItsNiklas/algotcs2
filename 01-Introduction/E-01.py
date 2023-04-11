fd = open(0)

N = int(fd.readline())

for line in fd.readlines():
    a, n = map(int, line.split())
    
    print(a**n)