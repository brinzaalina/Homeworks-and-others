#include "classes.h"
#include <iostream>
#include <cassert>
#include <cstring>

void function1() {
    SortedDictionary<int, std::string> d1{};
    d1.put(10, "j").put(2, "b").put(14, "m").put(1, "a");
    d1.print(std::cout);

    try {
        d1.put(2, "r");
        assert(false);
    } catch (std::runtime_error& e) {
        assert(strcmp(e.what(), "Element already exists!") == 0);
    }

    SortedDictionary<std::string, Person> d2{};
    Person p1{"Bianca", 20};
    Person p2{"Andrei", 21};
    d2.put("b", p1).put("a", p2);
    d2.print(std::cout);

    Person p = d2.eraseFirst();
    assert(p == p2);
    assert(d2.size() == 1);
}

int main() {
    function1();
    return 0;
}