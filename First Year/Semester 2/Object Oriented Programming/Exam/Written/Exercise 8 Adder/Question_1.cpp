//
// Created by selen on 19/06/2021.
//

#include <iostream>
#include <vector>

template <typename TElem>
class Adder {
private:
    std::vector<TElem> elements;
public:
    Adder(const TElem& elem);
    TElem sum();
    Adder<TElem> operator+(const TElem& element);
    Adder<TElem>& operator++();
    Adder<TElem>& operator--();
};

template<typename TElem>
Adder<TElem>::Adder(const TElem& elem) {
    this->elements.push_back(elem);
}

///The sum function computes the sum of all the elements
///\return - the result of the sum of the elements found
template<typename TElem>
TElem Adder<TElem>::sum() {
    TElem result = this->elements[0];
    for (auto elem: this->elements)
        result += elem;
    result = result - this->elements[0];
    return result;
}

template<typename TElem>
Adder<TElem> Adder<TElem>::operator+(const TElem &element) {
    this->elements.push_back(element);
    return *this;
}

template<typename TElem>
Adder<TElem>& Adder<TElem>::operator++() {
    TElem last = this->elements.back();
    this->elements.push_back(last);
    return *this;
}

template<typename TElem>
Adder<TElem>& Adder<TElem>::operator--() {
    if (this->elements.empty()) {
        std::string message;
        message.append("No more values!");
        throw std::runtime_error(message);
    }
    this->elements.pop_back();
    return *this;
}

void function2() {
    Adder<int> add { 5 };
    add = add + 5 + 2;
    ++add;
    add + 8;
    std::cout << add.sum() << "\n";
    --add;
    std::cout << add.sum() << "\n";
    --(--add);
    std::cout << add.sum() << "\n";
    try {
        --(--(--add));
    } catch (std::runtime_error& ex) {
        std::cout << ex.what() << "\n";
    }
}

int main() {
    function2();
    return 0;
}
