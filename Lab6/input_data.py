from sympy import *


def input_number(text):
    while True:
        try:
            number = int(input(text))
        except ValueError:
            print("Wrong input")
        else:
            return number


def input_float(text):
    while True:
        try:
            number = float(input(text))
        except ValueError:
            print("Wrong input")
        else:
            return number


def input_string(text):
    while True:
        try:
            str = input(text)
            str = parse_expr(str)
        except SyntaxError:
            print("Wrong function")
        else:
            return str