def advanced_euler_method(func, x0, y0, xn, step):
    x = [x0]
    y = [y0]
    current_x = x0
    current_y = y0
    while current_x < xn:
        current_res_func = func.subs([('x', current_x), ('y', current_y)]).evalf()
        delta_y = step * func.subs([('x', current_x + step/2), ('y', current_y + step/2 * current_res_func)]).evalf()
        current_y += delta_y
        current_x += step
        x.append(current_x)
        y.append(current_y)
    return x, y
