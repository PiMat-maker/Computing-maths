from sympy import *


def create_functions(coefs_diff, coefs_conditions):
    x, y, z1, z2 = symbols('x, y, z1, z2')
    if coefs_conditions[1] != 0:
        y1 = - y**2 - coefs_diff[0]*y + coefs_diff[1]
        y2 = -y * (z1 + coefs_diff[0]) + coefs_diff[2]
        y3 = z1 * y + z2
    else:
        y1 = - y ** 2 * coefs_diff[1] + y * coefs_diff[0] + 1
        y2 = - z1 * (y * coefs_diff[1] + coefs_diff[2])
        y3 = (y - z2) / z1
    return y1, y2, y3
