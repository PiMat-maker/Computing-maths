from math import log
from math import floor, ceil

from input_data import *
from graphics import *
from solve_task import *
import numpy as np
from sklearn.datasets import make_blobs


def do_polynomial_approximation(points, variables, degree):
    sums_x_in_different_pow = count_sums_x_in_different_pow(points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, points)
    first_coefs = count_coefs(functions, variables)
    differences = count_differences(first_coefs, points)

    index = index_of_the_biggest_difference(differences)
    for i in range(len(sums_x_in_different_pow)):
        sums_x_in_different_pow -= points[index][0] ** i

    second_points = np.delete(points, index, axis=0)
    sums_x_in_different_pow = count_sums_x_in_different_pow(second_points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, second_points)
    second_coefs = count_coefs(functions, variables)
    differences = count_differences(second_coefs, second_points)
    return [first_coefs, second_coefs, index]


def do_logarithmic_approximation(points, variables, degree):
    for i in range(len(points)):
        points[i][0] = log(points[i][0])
    sums_x_in_different_pow = count_sums_x_in_different_pow(points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, points)
    first_coefs = count_coefs(functions, variables)
    differences = count_differences(first_coefs, points)

    index = index_of_the_biggest_difference(differences)
    for i in range(len(sums_x_in_different_pow)):
        sums_x_in_different_pow -= points[index][0] ** i

    second_points = np.delete(points, index, axis=0)
    sums_x_in_different_pow = count_sums_x_in_different_pow(second_points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, second_points)
    second_coefs = count_coefs(functions, variables)
    return [first_coefs, second_coefs, index]


def do_exponential_approximation(points, variables, degree):
    for i in range(len(points)):
        points[i][1] = log(points[i][1])
    sums_x_in_different_pow = count_sums_x_in_different_pow(points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, points)
    first_coefs = count_coefs(functions, variables)
    differences = count_differences(first_coefs, points)

    index = index_of_the_biggest_difference(differences)
    for i in range(len(sums_x_in_different_pow)):
        sums_x_in_different_pow -= points[index][0] ** i

    second_points = np.delete(points, index, axis=0)
    sums_x_in_different_pow = count_sums_x_in_different_pow(second_points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, second_points)
    second_coefs = count_coefs(functions, variables)
    return [first_coefs, second_coefs, index]


def do_power_approximation(points, variables, degree):
    for i in range(len(points)):
        points[i][0] = log(points[i][0])
        points[i][1] = log(points[i][1])
    sums_x_in_different_pow = count_sums_x_in_different_pow(points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, points)
    first_coefs = count_coefs(functions, variables)
    differences = count_differences(first_coefs, points)

    index = index_of_the_biggest_difference(differences)
    for i in range(len(sums_x_in_different_pow)):
        sums_x_in_different_pow -= points[index][0] ** i

    second_points = np.delete(points, index, axis=0)
    sums_x_in_different_pow = count_sums_x_in_different_pow(second_points, degree)

    functions = make_linear_system(variables, sums_x_in_different_pow, second_points)
    second_coefs = count_coefs(functions, variables)
    return [first_coefs, second_coefs, index]
