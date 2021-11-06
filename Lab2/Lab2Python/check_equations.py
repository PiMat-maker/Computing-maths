from solve_equations import *
from input_data import *
from graph import *
from sympy import *

x = sp.symbols('x')
functions = [x ** 2 + 5 * x - 4,
             1 / 12 * x ** 4 + 1 / 3 * x - 1 / 60,
             2 * x - sin(x),
             x ** 2 - exp(- x)]
expressed_functions = [(-x ** 2 + 4) / 5, (-1 / 12 * x ** 4 + 1 / 60) * 3, sin(x) / 2, exp(-x / 2)]
num_of_equation = input_number("Choose the equation:\n"
                               "1) x ^ 2 + 5 * x = 4\n"
                               "2) 1/12 * x ** 4 + 1/3 * x = 1/60\n"
                               "3) 2 * x - sin(x) = 0\n"
                               "4)  x ** 2 - exp(-x) = 0\n")
precision = input_number("Input precision:\n")
function = functions[num_of_equation - 1]
expressed_function = expressed_functions[num_of_equation - 1]
draw_graph_equation(str(function), 'x')
left_border = input_float("Input borders:\n")
right_border = input_float("")

answer_curve = do_method_of_the_curve(left_border, right_border, function, precision)
if 'error' in answer_curve:
    print(answer_curve['error'])
else:
    print("Result:")
    print("Number of iterations:", answer_curve['iterations'])
    print("x =", answer_curve['result'], '+-', answer_curve['accuracy'])

answer_simple_iterations = do_method_of_simple_iterations_equations(left_border, right_border, expressed_function,
                                                                    precision)
if 'error' in answer_simple_iterations:
    print(answer_simple_iterations['error'])
else:
    print("Result:")
    print("Number of iterations:", answer_simple_iterations['iterations'])
    print("x =", answer_simple_iterations['result'], '+-',
          answer_simple_iterations['accuracy'] * answer_simple_iterations['coef'])
