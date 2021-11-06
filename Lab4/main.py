from math import floor, ceil
from approximation_methods import *
from input_data import *
from graphics import *
from solve_task import *
import numpy as np
from sklearn.datasets import make_blobs
import copy

points, y = make_blobs(n_samples=8, random_state=7, centers=1)
for i in range(len(points)):
    points[i][0] = abs(points[i][0])
    points[i][1] = abs(points[i][1])

num_of_approx_function = input_number("Choose one of the approximation functions:\n"
                                      "1) Polynomial\n"
                                      "2) Logarithmic\n"
                                      "3) Exponential\n"
                                      "4) Power\n")
degree = 1
if num_of_approx_function == 1:
    degree = input_number("Input degree of an approximation function\n")
x_symbols = []
x_template = 'x{number}'
for i in range(degree + 1):
    x_symbols.append(symbols(x_template.format(number=i)))

symbol = 'x'

if num_of_approx_function == 2:
    first_coefs, second_coefs, index = do_logarithmic_approximation(copy.deepcopy(points), x_symbols, degree)
    symbol = 'log(x)'
elif num_of_approx_function == 3:
    first_coefs, second_coefs, index = do_exponential_approximation(copy.deepcopy(points), x_symbols, degree)
elif num_of_approx_function == 4:
    first_coefs, second_coefs, index = do_power_approximation(copy.deepcopy(points), x_symbols, degree)
    symbol = 'log(x)'
else:
    first_coefs, second_coefs, index = do_polynomial_approximation(points, x_symbols, degree)

if num_of_approx_function == 3 or num_of_approx_function == 4:
    first_function = exp(first_coefs[0]) * exp(first_coefs[1] * symbols(symbol))
    second_function = exp(second_coefs[0]) * exp(second_coefs[1] * symbols(symbol))
else:
    first_function = bring_to_function(first_coefs, symbol)
    second_function = bring_to_function(second_coefs, symbol)

limits = [int(floor(min(points[:, 0]))), int(ceil(max(points[:, 0])))]
draw_graph_function(first_function, "red", "Before excluding", limits)
draw_graph_function(second_function, "gold", "After excluding", limits)
show_graph(np.delete(points, index, axis=0), points[index])

print("First coefficients")
for i in range(len(first_coefs)):
    print(x_symbols[i], "=", first_coefs[i])
print("Second coefficients")
for i in range(len(second_coefs)):
    print(x_symbols[i], "=", second_coefs[i])
