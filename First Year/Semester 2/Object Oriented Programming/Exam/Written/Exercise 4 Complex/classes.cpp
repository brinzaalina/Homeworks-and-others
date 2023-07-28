//
// Created by selen on 18/06/2021.
//

#include "classes.h"

Complex::Complex(): realPart{ 0 }, imaginaryPart{ 0 } {
}

Complex::Complex(int real, int imaginary): realPart{ real }, imaginaryPart{ imaginary } {
}

Complex::Complex(Complex &complexNumber) {
    this->realPart = complexNumber.realPart;
    this->imaginaryPart = complexNumber.imaginaryPart;
}

Complex::Complex(const Complex &complex) {
    this->realPart = complex.realPart;
    this->imaginaryPart = complex.imaginaryPart;
}

int Complex::getReal() const {
    return this->realPart;
}

int Complex::getImaginary() const {
    return this->imaginaryPart;
}

bool Complex::operator==(const Complex &complex) const {
    return (this->realPart == complex.realPart && this->imaginaryPart == complex.imaginaryPart);
}

std::ostream &operator<<(std::ostream &output, const Complex &complex) {
    std::string result;
    result.append(std::to_string(complex.realPart));
    result.append("+");
    result.append(std::to_string(complex.imaginaryPart));
    result.append("i");
    output << result;
    return output;
}

void Complex::setImaginary(int number) {
    this->imaginaryPart = number;
}

void Complex::setReal(int number) {
    this->realPart = number;
}

Complex Complex::operator/(int divisor) const {
    if (divisor == 0){
        std::string message;
        message.append("Division by zero!");
        throw error(message);
    }
    Complex result;
    int real = this->getReal() / divisor;
    result.setReal(real);
    int imaginary = this->getImaginary() / divisor;
    result.setImaginary(imaginary);
    return result;
}
