#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cassert>
#include <cstring>

///Computes if the greatest digit is on the last position of the number given as argument
///\param x - an integer number
///\return - 1 if the greatest digit is on the last position and 0 otherwise
///\throw - throws runtime error if the number given as argument has just a digit (such a number will return always true)
int fct1(int x) {
    if (x % 10 == x) {
        throw std::runtime_error{"Number contains a single digit"};
    }
    std::stringstream s;
    s << x;
    std::string str = s.str();
    int y = str.size();
    int i = 0;
    while (i < y - 1 && str[i] <= str[i + 1]) {
        i++;
    }
    return (i == y - 1);
}

void test(){
    int result;
    try {
        result = fct1(2);
        assert(result == 1);
    } catch (std::runtime_error& re) {
        assert(std::strcmp(re.what(), "Number contains a single digit") == 0);
    }

    result = fct1(24);
    assert(result == 1);

    result = fct1(42);
    assert(result == 0);

    result = fct1(23456789);
    assert(result == 1);

    result = fct1(23456798);
    assert(result == 0);
}

int main() {
    test();
    return 0;
}