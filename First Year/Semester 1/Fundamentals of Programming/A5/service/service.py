"""
    Service class includes functionalities for implementing program features
"""

from random import randint
from src.domain.entity import Complex, NumberException


class Service:
    """
    Class for the functions that implement the required functionalities.
    """

    def __init__(self):
        """
        Generates the initial list and the history list, necessary for the undo functionality.
        """
        self._numbers_list = [Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100)),
                              Complex(randint(-100, 100), randint(-100, 100))]
        self._history = []

    def add(self, real_part, imaginary_part):
        """
        Adds to the list the complex number read from the console.
        :param real_part: the real part of the number
        :param imaginary_part: the imaginary part of the number
        """
        for number in self._numbers_list:
            if real_part == number.real_part:
                if imaginary_part == number.imaginary_part:
                    raise ValueError("Number already exists in the list!")
        complex_number = Complex(real_part, imaginary_part)
        self._history.append(self._numbers_list[:])
        self._numbers_list.append(complex_number)

    def get_all(self):
        """
        Function for the display functionality, gets all the numbers in the list.
        """
        if len(self._numbers_list) == 0:
            raise ValueError("The list is empty!")
        return self._numbers_list[:]

    def filter(self, start, end):
        """
        This function filters the numbers in the list so that it contains only the numbers between start index and
        end index.
        :param start: the start index
        :param end: the end index
        """
        if start > end:
            raise ValueError("Start number greater than end number!")
        elif start < 0 or end < 0:
            raise ValueError("Invalid start or end!")
        elif start > len(self._numbers_list) - 1 or end > len(self._numbers_list) - 1:
            raise ValueError("Invalid start or end!")
        else:
            self._history.append(self._numbers_list[:])
            for number in self._numbers_list[::-1]:
                if start > self._numbers_list.index(number) or self._numbers_list.index(number) > end:
                    self._numbers_list.remove(number)

    def undo(self):
        """
        This function undoes the last operation that modified the data from the list of complex numbers.
        """
        if len(self._history) > 0:
            self._numbers_list = self._history.pop()
        else:
            if len(self._history) == 0:
                raise ValueError("Cannot undo because there is no action left to be undone!")

    def is_digit(self, character):
        """
        Function to test if a character is a digit
        :return: True if it is, False otherwise
        """
        for digit in range(0, 10):
            if str(digit) == character:
                return True
        return False

    def is_sign(self, character):
        """
        Function to test if a character is a sign
        :return: True if it is "+", "-", "." , False otherwise
        """
        return character == "+" or character == "-" or character == "."

    def create_integer_part(self, part_string, part_sign):
        """
        Function that creates the integer part
        :param part_string: the string of the number, digits
        :param part_sign: the sign of the number
        """
        part = int(part_string)
        if part_sign == "-":
            part = -part
        return part

    def get_number_parts(self, number_string):
        """
        Function that gets the number parts
        :param number_string: the number in its string form, as read from the console
        :return: real part sign and number, imaginary part sign and number
        """
        real_part_string = ""
        real_part_sign = ""
        imaginary_part_string = ""
        imaginary_part_sign = ""
        for i in range(len(number_string)):
            if self.is_digit(number_string[i]):
                if imaginary_part_sign == "":
                    real_part_string += number_string[i]
                else:
                    imaginary_part_string += number_string[i]
            elif self.is_sign(number_string[i]):
                if number_string[i] == ".":
                    if int(number_string[i + 1]) != 0:
                        raise NumberException("The number has decimal real or imaginary part!")
                if real_part_string == "":
                    real_part_sign = number_string[i]
                else:
                    imaginary_part_sign = number_string[i]
        return real_part_string, real_part_sign, imaginary_part_string, imaginary_part_sign

    def parse_number_string(self, number_string):
        """
        Function for parsing the number string
        :param number_string: the number in its string form
        :return: the real part and the imaginary part
        """
        real_part_string, real_sign, imaginary_part_string, imaginary_sign = self.get_number_parts(number_string)
        real_part = self.create_integer_part(real_part_string, real_sign)
        imaginary_part = self.create_integer_part(imaginary_part_string, imaginary_sign)
        return real_part, imaginary_part


def test_add():
    service = Service()
    real_part = 50
    imaginary_part = 50
    service.add(real_part, imaginary_part)
    numbers = service.get_all()
    assert str(numbers[len(numbers)-1]) == "50+50i"

    for index in range(5):
        real_part = randint(-10, 10)
        imaginary_part = randint(-10, 10)
        try:
            service.add(real_part, imaginary_part)
            numbers = service.get_all()
            if imaginary_part < 0:
                assert str(numbers[len(numbers)-1]) == str(real_part) + str(imaginary_part) + "i"
            else:
                assert str(numbers[len(numbers)-1]) == str(real_part) + "+" + str(imaginary_part) + "i"
        except AssertionError:
            assert True


def test_is_digit():
    character = "1"
    service = Service()
    assert service.is_digit(character) is True
    character = "+"
    assert service.is_digit(character) is False


def test_is_sign():
    character = "1"
    service = Service()
    assert service.is_sign(character) is False
    character = "+"
    assert service.is_sign(character) is True


def test_create_integer_part():
    part_string = "20"
    part_sign = "-"
    service = Service()
    assert service.create_integer_part(part_string, part_sign) == -20

    part_string = "9"
    part_sign = "+"
    assert service.create_integer_part(part_string, part_sign) == 9


def test_get_number_parts():
    number_string = "2+2i"
    service = Service()
    assert service.get_number_parts(number_string) == ('2', '', '2', '+')

    number_string = "-2i-2i"
    assert service.get_number_parts(number_string) == ('2', '-', '2', '-')


def test_parse_number_string():
    number_string = "2+2i"
    service = Service()
    assert service.parse_number_string(number_string) == (2, 2)

    number_string = "-2-2i"
    assert service.parse_number_string(number_string) == (-2, -2)


def test_all():
    test_add()
    test_is_digit()
    test_is_sign()
    test_create_integer_part()
    test_get_number_parts()
    test_parse_number_string()


test_all()
