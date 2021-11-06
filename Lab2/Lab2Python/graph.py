import numpy as np
import numexpr as ne
import sympy as sp
import re
import matplotlib.pyplot as plt
from math import e, log, sin, cos, tan, sqrt, isnan, acos


def count_points_system(func, length):
    points = []
    for valX in range(-5, 5):
        current_func = func.subs('x', valX)
        if length == 3:
            for valY in range(-5, 5):
                next_current_func = current_func.subs('y', valY)
                points.append([valX, valY, sp.solve(next_current_func, 'z')])
        else:
            points.append([valX, sp.solve(current_func, 'y')])
    return points


def count_points_equation(valX, func):
    return [valX, func.subs('x', valX)]


def is_not_complex_unknowns(points):
    for point in points:
        if re.search(r'[Iz]', str(point)):
            return False
    return True


def draw_solution_points(funcs):
    plt.scatter([-0.535595], [-2.506785], c='purple')


def draw_graph_equation(func, name_var):
    points = []
    x1 = np.linspace(-15, 5, 1000)
    prev = ne.evaluate(str(sp.parse_expr(func).subs(name_var, x1[0])))
    for i in range(1, len(x1)):
        cur = ne.evaluate(str(sp.parse_expr(func).subs(name_var, x1[i])))
        if cur * prev < 0:
            points.append((x1[i] + (x1[i - 1])) / 2)
        if cur == 0:
            points.append(x1[i])
        prev = cur
    for point in points:
        plt.scatter(point, 0, c='purple')
    y1 = lambda x: ne.evaluate(func)
    plt.plot(x1, y1(x1), c='red', label=func)
    plt.xlabel('$X$')
    plt.ylabel('$Y$')
    plt.legend(loc='upper left')
    plt.grid(c='#BFEFEF', ls='-', lw=0.5)
    plt.show()


def func11(value):
    return 3 * value - 0.9


def func12(value):
    return np.sin(value - 0.6) - 1.6


def draw_function2d(funcs, color, x1, label_func):
    for function in funcs:
        f1 = np.vectorize(function)
        tt = np.arange(-5, 5, 0.01)
        arr = []
        for i in range(len(tt)):
            if not isnan(function(tt[i])):
                arr.append(tt[i])
        plt.plot(arr, f1(arr), c=color, label=label_func)


def draw_graph_system():
    fig = plt.figure(figsize=(10, 10))
    x1 = np.linspace(-5, 5, 100)
    funcs = [[[func11], [func12]]]

    if len(funcs[0]) == 2:
        draw_solution_points(funcs)
        draw_function2d(funcs[0][0], 'red', x1, "3x - y = 0.9")
        draw_function2d(funcs[0][1], 'blue', x1, "sin(x - 0.6) - y = 1.6")
        plt.xlabel('$X$')
        plt.ylabel('$Y$')
        plt.legend(loc='upper left')
        plt.grid(c='#BFEFEF', ls='-', lw=0.5)
        plt.show()
