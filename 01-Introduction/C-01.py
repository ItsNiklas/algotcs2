import math

input = list(map(int, open(0).read().split()))

for x in input[1:]:
    a, b = False, False

    for r in range(1, 30):
        s = x / 2**r
        if s.is_integer():
            a = int(s) % 2 != 0
            
    for r in range(1, 19):
        s = x / 3**r
        if s.is_integer():
            b = int(s) % 3 != 0
    
    if a != b:
        print(x, end = ' ')
        
print()