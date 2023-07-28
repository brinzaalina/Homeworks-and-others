//
// Created by selen on 18/06/2021.
//

#pragma once
#include <vector>
#include <cassert>
#include <iostream>
#include <cstring>

class error: public std::runtime_error {
private:
public:
    explicit error(const std::string& what = " "): std::runtime_error(what) {}
};

class Complex {
private:
    int realPart;
    int imaginaryPart;
public:
    Complex();
    Complex(int real, int imaginary);
    Complex(Complex& complexNumber);
    Complex(const Complex& complex);
    int getReal() const;
    int getImaginary() const;
    void setImaginary(int number);
    void setReal(int number);
    bool operator==(const Complex& complex) const;
    Complex operator/(int divisor) const;
    friend std::ostream& operator<<(std::ostream& output, const Complex& complex);
};


template <typename TElem>
class Vector {
private:
    std::vector<TElem> elements;
public:
    explicit Vector(std::vector<TElem> elems);
    void printAll(std::ostream& output);
};

template<typename TElem>
Vector<TElem>::Vector(std::vector<TElem> elems) {
    this->elements = elems;
}

template<typename TElem>
void Vector<TElem>::printAll(std::ostream &output) {
    for (auto element: elements){
        output << element << ", ";
    }
    output << "\n";
}
