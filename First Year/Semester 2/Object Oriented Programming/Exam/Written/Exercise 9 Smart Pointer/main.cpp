#include <iostream>
#include <vector>
#include <algorithm>

class myException: public std::exception {
private:
    std::string message;
public:
    explicit myException(std::string& message): message(message) {}
    const char* what() const noexcept override { return message.c_str(); }
};

template <typename TElem>
class SmartPointer {
private:
    TElem* element;
public:
    explicit SmartPointer(TElem* element);
    friend std::ostream& operator<<(std::ostream& output, SmartPointer& smartPointer) {
        output << *smartPointer.element;
        return output;
    }
    bool operator==(const SmartPointer<TElem>& smartPointer);
    ~SmartPointer();
};

template <typename TElem>
SmartPointer<TElem>::SmartPointer(TElem *element) {
    this->element = element;
}

template<typename TElem>
bool SmartPointer<TElem>::operator==(const SmartPointer<TElem> &smartPointer) {
    return this->element == smartPointer.element;
}

template<typename TElem>
SmartPointer<TElem>::~SmartPointer() = default;

template <typename TElem>
class Vector: public std::vector<TElem> {
public:
    Vector() = default;
    Vector<TElem>& add(TElem& element);
    Vector<TElem> operator-(TElem& elem);
};

template<typename TElem>
Vector<TElem> &Vector<TElem>::add(TElem& element) {
    this->push_back(element);
    return *this;
}

template<typename TElem>
Vector<TElem> Vector<TElem>::operator-(TElem& elem) {
    int searched = -1;
    typename std::vector<TElem>::iterator it;
    it = std::find(this->begin(), this->end(), elem);
    if (it != this->end())
        searched = it - this->begin();
    if (searched == -1) {
        std::string ex;
        ex.append("Element does not exist!");
        throw myException(ex);
    } else {
        this->erase(this->begin() + searched);
    }
    return *this;
}

void function(){
    SmartPointer<int> i1{ new int{ 1 } };
    SmartPointer<int> i2{ new int{ 2 } };
    SmartPointer<int> i3{ new int{ 3 } };
    Vector<SmartPointer<int>> v1{};
    v1.add(i1).add(i2).add(i3);
    for (auto e: v1)
        std::cout << e << ", ";

    SmartPointer<std::string> s1{ new std::string{ "A" } };
    SmartPointer<std::string> s2{ new std::string{ "B" } };
    SmartPointer<std::string> s3{ new std::string{ "C" } };

    Vector<SmartPointer<std::string>> v2{};
    v2.add(s2).add(s1);
    try {
        v2 = v2 - s2;
        v2 = v2 - s3;
    } catch (std::exception& ex) {
        std::cout << ex.what();
    }
}

int main() {
    function();
    return 0;
}