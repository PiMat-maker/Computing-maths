from math import ceil
from input_data import *
from solver import *
from graphics import *
from equations_creator import *

x, y = symbols('x y')
functions = [x ** 2 - 2 * y, sin(x), 1 + exp(-x) * cos(pi * x) - y]
coefs_diffs = [[x + 1, 2, 2], [0, 1, x], [2*x, 2, 2*x**2]]
coefs_pairs = [[1, -1, -1, 1, 0, 4], [1, 0, 0, 1, 0, 0], [0, 1, 0, 1, 1, 0]]
num_of_diff_equation = input_number("Choose one of differential equations:\n"
                                    "1) y'' + (x+1)y' - 2y = 2\n"
                                    "2) y'' = x + y\n"
                                    "3) y'' + 2xy' - 2y = 2x^2\n")

function = functions[num_of_diff_equation - 1]
x0 = input_float("Input start point\nx >= ")
xn = input_float("Input end point\nx <= ")
precision = input_number("Input precision\n")
num_of_condition = input_number("Choose one of the pairs of equations:\n"
                                "1) y(" + str(x0) + ") - y'(" + str(x0) + ") = -1\n"
                                "   y(" + str(xn) + ") = 4\n"
                                "2) y(" + str(x0) + ") = 0\n"
                                "   y(" + str(xn) + ") = 0\n"
                                "3) y'(" + str(x0) + ") = 0\n"
                                "   y(" + str(xn) + ") + y'(" + str(xn) + ") = 0\n")

sys1, sys2, y0 = create_functions(coefs_diffs[num_of_diff_equation - 1], coefs_pairs[num_of_condition - 1])
h = 0.1 ** ceil(precision / 2)
z10, z20 = count_start_values(coefs_pairs[num_of_condition - 1])
z1_points, z2_points = straight_turn([sys1, sys2], [x0, xn], [z10, z20], h)
yn = count_start_y(coefs_pairs[num_of_condition - 1], z1_points[-1], z2_points[-1])
coords_x, coords_y = reverse_turn(y0, [x0, xn], z1_points, z2_points, yn, h)
for i in range(len(coords_y)-1, -1, -1):
    if not coords_y[i].is_real:
        coords_y.pop(i)
        coords_x.pop(i)
make_graph(coords_x, coords_y)
