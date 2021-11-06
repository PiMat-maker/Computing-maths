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