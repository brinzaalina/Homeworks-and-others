//
// Created by selen on 18/06/2021.
//

#include <vector>
#include <cassert>
#include <string>
#include <algorithm>

template <typename TElem>
auto fct1(std::vector<TElem> vector) {
    if (vector.empty())
        throw std::exception();
    TElem result;
    for (auto& a: vector)
        result += a;
    return result;
}

template <typename TElem>
TElem fct2(std::vector<TElem> vector) {
    if (vector.empty())
        throw std::exception();
    TElem max = vector[0];
    for (auto& a: vector)
        if (max < a)
            max = a;
    return max;
}

void testFct1() {
    std::vector<int> v1{ 4, 2, 1, -4};
    assert(fct1<int>(v1) == 3);
    std::vector<int> v2;
    try {
        fct1<int>(v2);
    } catch (std::exception&) {
        assert(true);
    }
    std::vector<double> v3{ 2, 10.5, 5, -10};
    assert(fct1<double>(v3) == 7.5);

    std::vector<std::string> v4{ "y", "q", "a", "m"};
    assert(fct1<std::string>(v4) == "yqam");
}

void testFct2() {
    std::vector<int> v1{ 4, 2, 1, 6, 3, -4};
    assert(fct2<int>(v1) == 6);
    std::vector<int> v2;
    try {
        fct2<int>(v2);
        assert(false);
    } catch (std::exception&) {
        assert(true);
    }
    std::vector<double> v3{ 2, 10.5, 6.33, -100, 9, 1.212};
    assert(fct2<double>(v3) == 10.5);

    std::vector<std::string> v4{ "y", "q", "a", "m"};
    assert(fct2<std::string>(v4) == "y");
}

int main(){
    testFct1();
    testFct2();
    return 0;
}