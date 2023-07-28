//
// Created by selen on 19/06/2021.
//

#include <iostream>
#include "classes.h"

SimpleIcecream::SimpleIcecream(std::string& description, double price){
    this->description = description;
    this->price = price;
}

std::string SimpleIcecream::getDescription() {
    std::string result;
    result.append("simple ice cream with ");
    result.append(this->description);
    return result;
}

double SimpleIcecream::computePrice() {
    return this->price;
}

IcecreamWithTopping::IcecreamWithTopping(Icecream *icecream) {
    this->icecream = icecream;
}

IcecreamWithChocolateTopping::IcecreamWithChocolateTopping(Icecream *icecream) : IcecreamWithTopping(icecream) {
}

std::string IcecreamWithChocolateTopping::addTopping() {
    std::string result;
    result.append(" with chocolate topping");
    return result;
}

std::string IcecreamWithChocolateTopping::getDescription() {
    std::string result;
    result.append(this->icecream->getDescription());
    result.append(this->addTopping());
    return result;
}

double IcecreamWithChocolateTopping::computePrice() {
    return this->icecream->computePrice() + 3;
}

IcecreamWithCaramelTopping::IcecreamWithCaramelTopping(Icecream *icecream) : IcecreamWithTopping(icecream) {
}

std::string IcecreamWithCaramelTopping::addTopping() {
    std::string result;
    result.append(" with caramel topping");
    return result;
}

std::string IcecreamWithCaramelTopping::getDescription() {
    std::string result;
    result.append(this->icecream->getDescription());
    result.append(this->addTopping());
    return result;
}

double IcecreamWithCaramelTopping::computePrice() {
    return this->icecream->computePrice() + 2;
}

void Order::addIcecream(Icecream *icecream) {
    this->icecreams.push_back(icecream);
}

void Order::printOrder() {
    for (auto icecream: this->icecreams)
        std::cout << icecream->getDescription() << " with the price " << icecream->computePrice() << "\n";
}
