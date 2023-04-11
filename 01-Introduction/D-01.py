fd = open(0)

N, M = map(int, fd.readline().split())

d = {}

for i, v in enumerate(map(int, fd.readline().split())):
    if v in d:
        d[v].append(i + 1)
    else:
        d[v] = [i + 1]

for x in fd.readlines():
    x = int(x)
    
    try:
        print(*d[x])
    except:
        print("None!")