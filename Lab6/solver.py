def advanced_euler_method(func, x0, y0, xn, step, sign):
    x = [x0]
    y = [y0]
    current_x = x0
    current_y = y0
    while current_x < xn:
        current_res_func = func.subs([('x', current_x), ('y', current_y)]).evalf()
        delta_y = step * func.subs([('x', current_x + step/2), ('y', current_y + step/2 * current_res_func)]).evalf()
        current_y += delta_y * sign
        current_x += step
        x.append(current_x)
        y.append(current_y)
    return y


def straight_turn(system, interval, start_values, step):
    z1_points = [start_values[0]]
    z2_points = [start_values[1]]
    current_x = interval[0] + step
    while current_x < interval[1]:
        new_point1 = advanced_euler_method(system[0], current_x, z1_points[-1], current_x + step, step, 1)
        new_point2 = advanced_euler_method(system[1].subs('z1', z1_points[-1]), current_x, z2_points[-1],
                                           current_x + step, step, 1)
        z1_points.append(new_point1[-1])
        z2_points.append(new_point2[-1])
        current_x += step

    return z1_points, z2_points


def reverse_turn(func, interval, z1_points, z2_points, yn, step):
    x = [interval[1]]
    y = [yn]
    current_x = x[-1] - step
    i = 2
    while current_x > interval[0]:
        new_y = advanced_euler_method(func.subs([('z1', z1_points[-i]), ('z2', z2_points[-i])]),
                                      current_x, y[-1], current_x + step, step, -1)
        x.append(current_x)
        y.append(new_y[-1])
        current_x -= step
        i += 1

    return x, y


def count_start_values(coefs_conditions):
    if coefs_conditions[1] != 0:
        z10 = - coefs_conditions[0]/coefs_conditions[1]
        z20 = coefs_conditions[2]/coefs_conditions[1]
    else:
        z10 = - coefs_conditions[1] / coefs_conditions[0]
        z20 = - coefs_conditions[2] / coefs_conditions[0]
    return z10, z20


def count_start_y(coefs_conditions, z1n, z2n):
    if coefs_conditions[1] != 0:
        yn = (coefs_conditions[5] - coefs_conditions[4] * z2n) / (coefs_conditions[3] + coefs_conditions[4] * z1n)
    else:
        yn = (coefs_conditions[5] * z1n + coefs_conditions[4] * z2n) / (coefs_conditions[4] + coefs_conditions[3] * z1n)
    return yn
