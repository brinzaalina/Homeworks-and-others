"""
    Entity class should be coded here
"""
from random import randint


class NumberException(Exception):
    def __init__(self, msg):
        self._msg = msg


def is_integer_num(number):
    if isinstance(number, int):
        return True
    elif isinstance(number, float):
        if number.is_integer():
            return True
    return False


class Complex:
    """
    Represent one complex number
    """

    def __init__(self, real_part, imaginary_part):
        """
        Create complex number
        :param real_part: The real part of the number
        :param imaginary_part: The imaginary part of the number
        """
        if is_integer_num(real_part):
            if not is_integer_num(imaginary_part):
                raise NumberException("Imaginary part not integer!")
        elif not is_integer_num(real_part):
            if is_integer_num(imaginary_part):
                raise NumberException("Real part not integer!")
            elif not is_integer_num(imaginary_part):
                raise NumberException("Real and imaginary parts not integers!")

        self._real = real_part
        self._imaginary = imaginary_part

    @property
    def real_part(self):
        return self._real

    @property
    def imaginary_part(self):
        return self._imaginary

    def __str__(self):
        if self._imaginary < 0:
            return str(int(self._real)) + '-' + str(-int(self._imaginary)) + "i"
        elif self._imaginary >= 0:
            return str(int(self._real)) + '+' + str(int(self._imaginary)) + "i"


def test_complex():
    complex_number = Complex(2, 3)
    assert complex_number.real_part == 2, 'real part is wrong'
    assert complex_number.imaginary_part == 3

    for index in range(20):
        real = randint(-100, 100)
        imaginary = randint(-100, 100)
        try:
            number = Complex(real, imaginary)
            assert is_integer_num(number.real_part) is True, str(real) + " -> real has a decimal"
            assert is_integer_num(number.imaginary_part) is True, str(imaginary) + " -> imaginary has a decimal"
        except NumberException:
            assert True


test_complex()
