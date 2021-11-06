import sympy as sp
from sympy import *
from input_data import *
from method_of_trapezoid import *
import numpy as np


x = sp.symbols('x')
functions = [x ** 2 + 5 * x - 4, 1/12 * x ** 4 + 1/3 * x - 1/60, (2 * x * (x + 3) ** 2) / (x + 3) + 6, 1 / sin(x)]
num_of_integral = input_number("Choose one of the integrals:\n"
                               "1) \u222B x ** 2 + 5 * x - 4 dx\n"
                               "2) \u222B 1/12 * x ** 4 + 1/3 * x - 1/60 dx\n"
                               "3) \u222B (2 * x * (x + 3) ** 2) / (x + 3) + 6 dx\n"
                               "4) \u222B 1 / sin(x) dx\n")
precision = input_number("Input precision:\n")
left_border = input_float("Input borders:\n")
right_border = input_float("")
function = functions[num_of_integral - 1]
sum_coef = 1
if left_border > right_border:
    left_border, right_border = right_border, left_border
    sum_coef = -1

# Find discontinuities and make borders
if len(find_discontinuities(left_border, right_border, function)) != 0:
    print("Can't count integral: There are excludes")
else:
    borders = [[left_border, right_border]]
    num_of_sections_for_border = [
        count_number_of_steps_in_section(borders[i][0], borders[i][1], function, precision)
        for i in range(len(borders))]

    integral_result = sum(
        [count_integral_of_the_segment(borders[i][0], borders[i][1], function, num_of_sections_for_border[i])
         for i in range(len(borders))])

    integral_result_prev = sum(
        [count_integral_of_the_segment(borders[i][0], borders[i][1], function, (num_of_sections_for_border[i] + 1) / 2)
         for i in range(len(borders))])

    print("Result of integral:", sum_coef*integral_result)
    print("Number of segments:", sum(num_of_sections_for_border))
    print("Accuracy:", 1 / 3 * abs(integral_result - integral_result_prev))
