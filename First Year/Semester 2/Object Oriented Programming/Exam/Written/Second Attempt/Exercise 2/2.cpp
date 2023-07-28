
#include <vector>
#include <cassert>
#include <string>

template <typename Type>
///Computes the sum of the elements starting from the last one
///\tparam TElem is the type of the elements
///\param elements the vector for which the sum is computed
///\return the sum
///\throw exception if the vector is empty
Type fct(std::vector<Type> elements) {
    if (elements.empty())
        throw std::exception();
    Type sum{};
    for (auto& element: elements) {
        sum = element + sum;
    }
    return sum;
}

void testFct() {
    std::vector<int> v1 { 4, 2, 1, -4 };
    assert(fct<int>(v1) == 3);
    std::vector<int> v2;
    try {
        fct<int>(v2);
        assert(false);
    } catch (std::exception&) { assert(true); }

    std::vector<double> v3{ 2, 10.5, 5, -10 };
    assert(fct<double>(v3) == 7.5);

    std::vector<std::string> v4{ "y", "q", "a", "m" };
    assert(fct<std::string>(v4) == "maqy");
}

int main() {
    testFct();
    return 0;
}