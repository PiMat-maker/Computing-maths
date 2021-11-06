from math import pi, nan, ceil
import sympy as sp
import numpy as np
from sympy import zoo


def checkDAV(func, left_limit, right_limit):
    discountinuities = []
    if func.find('tan') != -1:
        if (right_limit - pi/2)//pi != (left_limit - pi/2)//pi:
            discountinuities.append(pi / 2)
            return discountinuities
    if func.find('log') != -1:
        if left_limit <= 0:
            discountinuities.append(0)
            return discountinuities
    pos = func.find('/')
    if pos == -1:
        return discountinuities

    func = func[pos:]
    if func.find('cos') != -1:
        if (right_limit - pi/2)//pi != (left_limit - pi/2)//pi:
            discountinuities.append(pi / 2)
            return discountinuities
    if func.find('sin') != -1:
        if right_limit // pi != left_limit // pi:
            discountinuities.append(pi)
            return discountinuities
    return discountinuities


def take_derivative(func, variable):
    return sp.diff(func, variable)


def find_critical_points(func):
    diff = take_derivative(func, 'x')
    crit_points = [x for x in sp.solve(diff, 'x') if x.is_real]
    return crit_points


def find_discontinuities(left_limit, right_limit, func):
    str_func = str(func)
    discontinuities = checkDAV(str_func, left_limit, right_limit)
    if len(discontinuities) != 0:
        return discontinuities
    discontinuities = [x for x in sp.solve(func ** (-1), 'x', check=False)
                       if x.is_real and left_limit <= x <= right_limit]
    if len(discontinuities) != 0:
        return discontinuities

    x = np.linspace(left_limit, right_limit, int(right_limit - left_limit) * 1000)
    discontinuities = [point for point in x if func.subs('x', point) is zoo or func.subs('x', point) == nan]
    return discontinuities


def count_number_of_steps_in_section(left_limit, right_limit, func, precision):
    second_diff = take_derivative(take_derivative(func, 'x'), 'x')
    crit_points = find_critical_points(second_diff)

    max_value = max(abs(second_diff.subs('x', left_limit).evalf()), abs(second_diff.subs('x', right_limit).evalf()))
    for crit_point in crit_points:
        if left_limit <= crit_point <= right_limit:
            max_value = max(max_value, abs(second_diff.subs('x', crit_point).evalf()))

    num_of_steps = ceil((max_value * (right_limit - left_limit) ** 3 / (12 * 0.1 ** precision)) ** (1/2))
    return num_of_steps


def count_integral_of_the_segment(left_limit, right_limit, func, num_of_sections):
    sum = 0
    step = (right_limit - left_limit) / num_of_sections
    left_res = func.subs('x', left_limit).evalf()
    while left_limit < right_limit:
        right_res = func.subs('x', left_limit + step).evalf()
        sum += (right_res + left_res) / 2 * step
        left_res = right_res
        left_limit += step

    return sum