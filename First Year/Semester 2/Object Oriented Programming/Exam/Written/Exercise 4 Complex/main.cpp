//
// Created by selen on 18/06/2021.
//

#include "classes.h"

void complex() {
    Complex a{}, b{ 1, 2 }, c{ 6, 4 }, d { b };
    assert(a.getReal() == 0 && a.getImaginary() == 0);
    assert(c.getImaginary() == 4);
    assert(b == d);
    Complex res1 = c / 2;
    std::cout << res1 << "\n";
    try {
        Complex res2 = b / 0;
    } catch (std::runtime_error& e) {
        assert(strcmp(e.what(), "Division by zero!") == 0);
    }

    Vector<std::string> v1{ std::vector<std::string>{ "hello", "bye" } };
    v1.printAll(std::cout);

    Vector<Complex> v2{ std::vector<Complex>{a, b, c, d} };
    v2.printAll(std::cout);
}

int main() {
    complex();
    return 0;
}