from cmath import *
import math


def angle_between(a, b, c, d):
    # calculate the dot product
    dot_product = a * c + b * d

    # calculate the magnitude of the complex numbers
    magnitude_z1 = sqrt(a**2 + b**2)
    magnitude_z2 = sqrt(c**2 + d**2)

    # calculate the cosine of the angle
    cos_theta = dot_product / (magnitude_z1 * magnitude_z2)

    # calculate the angle in radians
    return math.acos(cos_theta.real)


N = int(input())
targets = [map(int, input().split()) for _ in range(N)]

res = (angle_between(u, v, x, y) / (2 * pi) for u, v, x, y in targets)

print("{:.9f}".format(sum(res)))
