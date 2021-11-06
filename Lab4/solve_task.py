from sympy import *


def make_linear_system(variables, sums, points):
    funcs = []
    for i in range(len(variables)):
        values = [variables[j] * sums[i + j]
                  for j in range(len(variables))]
        funcs.append(sum(values) - sum(points[:, 0] ** i * points[:, 1]))
    return funcs


def count_coefs(funcs, variables):
    coefs = linsolve(funcs, variables).args[0]
    coefs = rid_of_free_variables(coefs, variables)
    return coefs


def index_of_the_biggest_difference(differences):
    max = differences[0]
    index = 0
    for i in range(1, len(differences)):
        if max < differences[i]:
            max = differences[i]
            index = i
    return index


def count_differences(coefs, points):
    differences = []
    for i in range(len(points)):
        total = 0
        for j in range(len(coefs)):
            total += coefs[j] * points[i][0] ** j
        differences.append(abs(total - points[i][1]))
    return differences


def count_sums_x_in_different_pow(points, degree):
    sums = []
    for i in range(2 * degree + 1):
        sums.append(sum(points[:, 0] ** i))
    return sums


def rid_of_free_variables(coefs, variables):
    list_of_values = [(variables[i], 1) for i in range(len(variables))]
    new_coefs = []
    for i in range(len(coefs)):
        new_coefs.append(coefs[i].subs(list_of_values).evalf())
    return new_coefs