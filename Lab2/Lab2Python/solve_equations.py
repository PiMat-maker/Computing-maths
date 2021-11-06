from sympy import *
from solve_systems import *


def is_converge_by_curve(left_limit, right_limit, func):
    return func.subs('x', left_limit).evalf() * func.subs('x', right_limit).evalf() < 0


def is_start_point(x, func):
    return func.subs('x', x).evalf() * take_derivative(take_derivative(func, 'x'), 'x').subs('x', x).evalf() > 0


def do_iterations(current_point, func, precision):
    coef = 1
    iteration = 0
    while abs(coef) > 0.1 ** precision:
        coef = func.subs('x', current_point).evalf() / take_derivative(func, 'x').subs('x', current_point).evalf()
        current_point -= coef
        iteration += 1

    accuracy = coef
    return {'iterations': iteration, 'result': current_point, 'accuracy': accuracy}


def do_method_of_the_curve(left_limit, right_limit, func, precision):
    if not is_converge_by_curve(left_limit, right_limit, func):
        return {'error': "Doesn't converge by method of the curve"}
    start_point = oo
    if is_start_point(left_limit, func):
        start_point = left_limit
    if start_point == oo and is_start_point(right_limit, func):
        start_point = right_limit
    if start_point != oo:
        return do_iterations(start_point, func, precision)
    else:
        return {'error': "No start point"}


def find_critical_points(func, name_var):
    diff = take_derivative(func, name_var)

    crit_points = [x for x in sp.solve(diff, name_var) if x.is_real]
    return crit_points


def count_coefficient(left_limit, right_limit, func):
    diff = take_derivative(func, 'x')
    crit_points = find_critical_points(diff, 'x')

    max_value = max(abs(diff.subs('x', left_limit).evalf()), abs(diff.subs('x', right_limit).evalf()))
    for crit_point in crit_points:
        if left_limit <= crit_point <= right_limit:
            max_value = max(max_value, abs(func.subs('x', crit_point).evalf()))

    return max_value


def is_converge_by_simple_iterations(left_limit, right_limit, func):
    max_value = count_coefficient(left_limit, right_limit, func)

    if max_value >= 1:
        return False

    mid = (right_limit + left_limit) / 2
    return abs(func.subs('x', mid).evalf() - mid) < (1 - max_value) * (mid - left_limit)


def do_iterations_method_of_simple_iterations(current_point, func, precision):
    prev_point = current_point
    current_precision = 1
    iteration = 0
    while current_precision > 0.1 ** precision:
        current_point = func.subs('x', prev_point).evalf()
        current_precision = abs(current_point - prev_point)
        prev_point = current_point
        iteration += 1

    return {'iterations': iteration, 'result': current_point, 'accuracy': current_precision}


def do_method_of_simple_iterations_equations(left_limit, right_limit, func, precision):
    if not is_converge_by_simple_iterations(left_limit, right_limit, func):
        return {'error': "Doesn't converge by method of simple iterations"}

    answer = do_iterations_method_of_simple_iterations((left_limit + right_limit) / 2, func, precision)
    coef = count_coefficient(left_limit, right_limit, func)
    answer['coef'] = coef
    return answer
