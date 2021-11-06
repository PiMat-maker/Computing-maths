import numpy as np
import sympy as sp


def express_unknowns(function, variable):
    return sp.solve(sp.parse_expr(function), variable)


def make_expressed_functions(funcs, name_vars):
    ex_functions = []
    for i in range(len(funcs)):
        ex_functions.append(express_unknowns(funcs[i], name_vars[i])[0])
    return ex_functions


def take_derivative(function, variable):
    return sp.diff(function, variable)


def find_derivatives(funcs, name_vars):
    diffs = []
    for i in range(len(funcs)):
        row_of_diffs = []
        for j in range(len(funcs)):
            row_of_diffs.append(take_derivative(funcs[i], name_vars[j]))
        diffs.append(row_of_diffs)
    return diffs


def find_critical_points(diffs, name_vars):
    second_diffs = []
    for i in range(len(diffs)):
        row_of_diffs = []
        for j in range(len(diffs[i])):
            row_of_diffs.append(take_derivative(diffs[i][j], name_vars[j]))
        second_diffs.append(row_of_diffs)

    crit_points = []
    for i in range(len(second_diffs)):
        row_of_crit_points = []
        for j in range(len(second_diffs[i])):
            row_of_crit_points.append(sp.solve(second_diffs[i][j], name_vars[j]))
        crit_points.append(row_of_crit_points)
    return crit_points


def find_max_abs_on_the_interval(crit_points_func, function, variable, interval):
    maximum = 0
    for crit_point in crit_points_func:
        if interval[0] <= crit_point <= interval[1]:
            maximum = max(maximum, abs(function.subs(variable, crit_point)))

    left_border = abs(function.subs(variable, interval[0]))
    right_border = abs(function.subs(variable, interval[1]))
    maximum_between_borders = max(left_border, right_border)
    return max(maximum, maximum_between_borders)


def is_converging(crit_points, diffs, name_vars, intervals):
    for i in range(len(crit_points)):
        sum = 0
        for j in range(len(crit_points[i])):
            sum += find_max_abs_on_the_interval(crit_points[i][j], diffs[i][j], name_vars[j], intervals[j])
        if sum >= 1:
            return False
    return True


def do_method_of_simple_iterations(ex_functions, intervals, precision, name_vars):
    result = {'unknowns': [], 'precisions': [], 'iterations': 0}
    current_step = [0.0, 0.0]
    previous_step = [np.mean(intervals[0]), np.mean(intervals[1])]
    precisions = [0.0, 0.0]
    current_precision = 1
    iteration = 0
    while current_precision >= pow(0.1, precision):
        for i in range(len(previous_step)):
            if intervals[i][0] > previous_step[i] or intervals[i][1] < previous_step[i]:
                return result

        for i in range(len(ex_functions)):
            current_step[i] = (ex_functions[i].subs([(name_vars[0], previous_step[0]), (name_vars[1], previous_step[1])])).evalf()

        for i in range(len(current_step)):
            precisions[i] = abs(current_step[i] - previous_step[i])

        current_precision = max(precisions)

        for i in range(len(current_step)):
            previous_step[i] = current_step[i]
        iteration += 1

    result['unknowns'] = previous_step
    result['precisions'] = precisions
    result['iterations'] = iteration
    return result