import matplotlib.pyplot as plt
import numpy as np
from sympy import *
import numexpr as ne


def bring_to_function(coefs, symbol):
    x = symbols(symbol)
    values = [coefs[i] * x ** i for i in range(len(coefs))]
    return sum(values)


def draw_graph_function(func, color, text, limits):
    x1 = np.linspace(limits[0], limits[1], 100)
    y1 = lambda x: ne.evaluate(str(func))
    plt.plot(x1, y1(x1), color=color, label=text)


def show_graph(points, excluding_point):
    plt.scatter(points[:, 0], points[:, 1])
    plt.scatter(excluding_point[0], excluding_point[1], color="grey")
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.show()
