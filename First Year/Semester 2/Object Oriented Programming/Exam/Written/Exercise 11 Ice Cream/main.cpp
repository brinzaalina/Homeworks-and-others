//
// Created by selen on 19/06/2021.
//

#include "classes.h"

void test() {
    std::string type1 = "vanilla ice cream";
    auto vanilla = new SimpleIcecream{type1, 2.5};
    std::string type2 = "pistachio ice cream";
    auto pistachio = new SimpleIcecream{type2, 4};
    std::string type3 = "chocolate ice cream";
    auto chocolate = new SimpleIcecream{type3, 2};

    auto pistachioWithChocolate = new IcecreamWithChocolateTopping{pistachio};
    auto pistachioWithChocolateCaramel = new IcecreamWithCaramelTopping{pistachioWithChocolate};

    auto chocolateWithCaramel = new IcecreamWithCaramelTopping{chocolate};

    Order order{};
    order.addIcecream(vanilla);
    order.addIcecream(pistachioWithChocolateCaramel);
    order.addIcecream(chocolateWithCaramel);

    order.printOrder();
}

int main() {
    test();
    return 0;
}

