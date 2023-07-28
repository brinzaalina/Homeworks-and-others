#include <cassert>
#include <vector>
#include <iostream>
#include <cstring>

class Rational {
private:
    int numerator;
    int denominator;
public:
    Rational(): numerator{0}, denominator{1} {}
    Rational(int numerator, int denominator): numerator{numerator}, denominator{denominator} {}
    Rational(Rational& rational){
        this->numerator = rational.numerator;
        this->denominator = rational.denominator;
    }
    Rational(const Rational& rational) {
        this->numerator = rational.numerator;
        this->denominator = rational.denominator;
    }
    int getNumerator() const {
        return this->numerator;
    }
    void setNumerator(int number) {
        this->numerator = number;
    }
    int getDenominator() const {
        return this->denominator;
    }
    void setDenominator(int number) {
        this->denominator = number;
    }
    bool operator==(const Rational& rational) const {
        return this->numerator == rational.numerator && this->denominator == rational.denominator;
    }
    Rational operator/(Rational& rational) const {
        if (rational.numerator == 0)
            throw std::runtime_error("Division by zero!");
        Rational result;
        int number_n = this->numerator * rational.denominator;
        int number_d = this->denominator * rational.numerator;
        result.setNumerator(number_n);
        result.setDenominator(number_d);
        return result;
    }
    friend std::ostream& operator<<(std::ostream& ostream, const Rational& rational) {
        std::string result;
        result.append(std::to_string(rational.numerator));
        result.append("/");
        result.append(std::to_string(rational.denominator));
        ostream << result;
        return ostream;
    }
};

template <typename TElem>
class Vector {
private:
    std::vector<TElem> elements;
public:
    explicit Vector(std::vector<TElem> elements) {
        this->elements = elements;
    }
    void printAll(std::ostream& ostream) {
        for (auto& element: this->elements) {
            ostream << element << ", ";
        }
        ostream << "\n";
    }
};

void rational() {
    Rational a{}, b{6, 15}, c{3, 5}, d{b};
    assert(a.getNumerator() == 0);
    assert(c.getDenominator() == 5);
    assert(b == d);
    Rational res1 = b / c;
    std::cout << res1 << "\n"; // prints: 30/45
    try {
        Rational res2 = b / a;
    } catch (std::runtime_error& e) {
        assert(strcmp(e.what(), "Division by zero!") == 0);
    }
    Vector<int> v1{std::vector<int>{1, 2, 3}};
    v1.printAll(std::cout); // prints: 1, 2, 3,

    Vector<Rational> v2{ std::vector<Rational>{a, b, c, d}};
    v2.printAll(std::cout); // prints: 0/1, 6/15, 3/5, 6/15
}

int main() {
    rational();
    return 0;
}