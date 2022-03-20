# Implementation for A2


"""
Implement a menu-driven console application that provides the following functionalities:
    1. Read a list of complex numbers (in z = a + bi form) from the console.
    2. Display the entire list of numbers on the console.
    3. Display on the console the longest sequence that consists of real numbers.
    4. Display on the console the longest sequence that consists of distinct numbers.
    5. Exit the application.

The source code will include:
    - specifications for the functions related to point 3 and 4 above.
    - 10 complex numbers already available at program startup.
"""


"""
Requirements:
    - use functions to: read a complex number from the console, write a complex number to the console, implement
    each required functionality.
    - functions communicate using input parameter(s) and the return statement (DO NOT use global variables).
    - each complex number should be represented as a list, tuple or dictionary (e.g. 1-2i as [1, -2], (1, -2) or 
    {'real': 1, 'imag': -2}. To access or modify numbers, use getter and setter functions.
    - separate input/output functions (those using print and input statements) from those performing the calculations 
    (see program.py)
    - provide the user with a menu-driven console-based user interface. Input data should be read from the console
    and the results printed to the console. At each step, the program must provide the user the context of the operation 
    (do not display an empty prompt).
"""

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities


def read_number():
    number_string = input("number: ")
    number = parse_number_string(number_string)
    return number


def read_number_list(numbers):
    counter = int(input("How many numbers should we read? "))
    for i in range(counter):  # 0 -> counter - 1
        number = read_number()
        numbers.append(number)
    print("Numbers successfully added to the list!")


def print_number(number):
    print(str(get_real_part(number)) + " + " + str(get_imaginary_part(number)) + "i")


def show_menu():
    print("1. Read a list of complex numbers in 'a + bi' form from the console")
    print("2. Display the entire list of complex numbers")
    print("3. Display the longest sequence that has only real numbers")
    print("4. Display the longest sequence that has distinct numbers")
    print("5. Exit the application")


def start():
    done = False
    complex_numbers = [create_complex_number(1, 0),
                       create_complex_number(2, 3),
                       create_complex_number(2, 3),
                       create_complex_number(4, 5),
                       create_complex_number(10, 0),
                       create_complex_number(3, 0),
                       create_complex_number(-100, 0),
                       create_complex_number(-100, 0),
                       create_complex_number(10, -2),
                       create_complex_number(3, -3)]
    while not done:
        show_menu()
        user_choice = int(input("Your choice: "))
        if user_choice == 1:
            read_number_list(complex_numbers)
        elif user_choice == 2:
            display_number_list(complex_numbers)
        elif user_choice == 3:
            display_longest_real_sequence(complex_numbers)
        elif user_choice == 4:
            display_longest_distinct_sequence(complex_numbers)
        elif user_choice == 5:
            done = True
            print("Bye bye!")
        else:
            print("Bad input!")


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


def create_complex_number(real_part, imaginary_part):
    return {"real": real_part, "imaginary": imaginary_part}


def get_real_part(complex_number):
    return complex_number["real"]


def get_imaginary_part(complex_number):
    return complex_number["imaginary"]


def set_real_part(complex_number, real_part):
    complex_number["real"] = real_part


def set_imaginary_part(complex_number, imaginary_part):
    complex_number["imaginary"] = imaginary_part


def equal(complex_number, other_complex_number):
    """
    This function computes whether two complex numbers are equal
    :param complex_number: a complex number
    :param other_complex_number: another complex number
    :return: True if the given complex numbers are equal
             False otherwise
    """
    if get_real_part(complex_number) == get_real_part(other_complex_number) and get_imaginary_part(complex_number) == get_imaginary_part(other_complex_number):
        return True
    else:
        return False


def is_digit(character):
    for digit in range(0, 10):
        if str(digit) == character:
            return True
    return False


def is_sign(character):
    return character == "+" or character == "-"


def create_integer_part(part_string, part_sign):
    part = int(part_string)
    if part_sign == "-":
        part = -part
    return part


def parse_number_string(number_string):
    real_part_string, real_sign, imaginary_part_string, imaginary_sign = get_number_parts(number_string)
    real_part = create_integer_part(real_part_string, real_sign)
    imaginary_part = create_integer_part(imaginary_part_string, imaginary_sign)
    number = create_complex_number(real_part, imaginary_part)
    return number


def get_number_parts(number_string):
    real_part_string = ""
    real_part_sign = ""
    imaginary_part_string = ""
    imaginary_part_sign = ""
    for i in range(len(number_string)):
        if is_digit(number_string[i]):
            if imaginary_part_sign == "":
                real_part_string += number_string[i]
            else:
                imaginary_part_string += number_string[i]
        elif is_sign(number_string[i]):
            if real_part_string == "":
                real_part_sign = number_string[i]
            else:
                imaginary_part_sign = number_string[i]
    return real_part_string, real_part_sign, imaginary_part_string, imaginary_part_sign


def display_number_list(numbers):
    for number in numbers:
        print_number(number)


def is_real(complex_number):
    """
    This function tells if a complex number is real or not
    :param complex_number: a complex number
    :return: True if the number is real
             False otherwise
    """
    if get_imaginary_part(complex_number) == 0:
        return True
    else:
        return False


def get_longest_real_sequence(complex_numbers):
    """
    This function computes the longest sequence of complex numbers formed only by real numbers
    :param complex_numbers: list - the list of complex numbers
    :return: sequence: list - desired longest sequence of real complex numbers
    """
    sequence = []  # the current sequence
    best_sequence = []  # best overall sequence
    for number in complex_numbers:
        if is_real(number):
            sequence.append(number)
        else:
            sequence = []

        if len(sequence) > len(best_sequence):
            best_sequence = sequence[:]
    return best_sequence


def display_longest_real_sequence(complex_numbers):
    """
    This function displays the longest sequence of complex numbers formed only by real numbers
    :param complex_numbers: list - the list of complex numbers
    :return: nothing
    """
    sequence = get_longest_real_sequence(complex_numbers)
    display_number_list(sequence)


def has_distinct_numbers(sequence):
    """
    This function computes whether a list has only distinct elements or not
    :param sequence: a given list
    :return: True if all the elements are distinct
             False otherwise
    """
    for i in range(len(sequence) - 1):
        for j in range(i + 1, len(sequence)):
            if equal(sequence[i], sequence[j]):
                return False
    return True


def get_longest_distinct_sequence(complex_numbers):
    """
    This function computes the longest sequence of complex numbers formed only by distinct numbers
    :param complex_numbers: list - the list of complex numbers
    :return: sequence: list - desired longest sequence of distinct complex numbers
    """
    best_sequence = []  # best overall sequence
    for i in range(len(complex_numbers)):
        for j in range(i, len(complex_numbers)):
            sequence = complex_numbers[i:j+1]
            if has_distinct_numbers(sequence):
                if len(sequence) > len(best_sequence):
                    best_sequence = sequence[:]
    return best_sequence


def display_longest_distinct_sequence(complex_numbers):
    """
    This function displays the longest sequence of complex numbers formed only by distinct numbers
    :param complex_numbers: list - the list of complex numbers
    :return: nothing
    """
    sequence = get_longest_distinct_sequence(complex_numbers)
    display_number_list(sequence)


start()
