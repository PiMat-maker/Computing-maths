from solve_systems import *
from input_data import *
from graph import *


x, y = sp.symbols('x y')
functions = [["3 * x - y - 0.9",
             "sin(x - 0.6) - y - 1.6"]]
num_of_equation = input_number("Choose the equation:\n"
                               "1) 3 * x - y - 0.9\n"
                               "sin(x - 0.6) - y - 1.6\n")
precision = input_number("Input precision:\n")
functions_of_system = functions[0]
draw_graph_system()
left_border_x = input_float("Input borders for x:\n")
right_border_x = input_float("")
left_border_y = input_float("Input borders for y:\n")
right_border_y = input_float("")
variables = [x, y]
borders = [[left_border_x, right_border_x], [left_border_y, right_border_y]]

expressed_functions = make_expressed_functions(functions_of_system, variables)

derivatives = find_derivatives(expressed_functions, variables)

critical_points = find_critical_points(derivatives, variables)

if not is_converging(critical_points, derivatives, variables, borders):
    print("Functions don't converge by method of simple iterations")
else:
    answer = do_method_of_simple_iterations(expressed_functions, borders, precision, variables)
    if answer['unknowns'] is None:
        print("No answer by method of simple iterations")
    else:
        print("Result:")
        print("Number of iterations:", answer['iterations'])
        for i in range(len(answer['unknowns'])):
            print(variables[i], "=", answer['unknowns'][i], "+-", "{0:.10f}".format(answer['precisions'][i] * 0.07))
