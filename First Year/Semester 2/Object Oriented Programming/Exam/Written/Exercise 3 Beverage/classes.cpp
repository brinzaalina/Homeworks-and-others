#include "classes.h"

Beverage::Beverage(std::string description) {
    this->description = std::move(description);
}

void Beverage::print() {
    std::string beverage;
    beverage.append(this->getDescription());
    beverage.append(" with the price ");
    beverage.append(std::to_string(this->price()));
    std::cout << beverage;
}

std::string Beverage::getDescription() {
    return this->description;
}

Beverage::~Beverage() = default;


Coffee::Coffee(): Beverage{"Coffee"} {
}

double Coffee::price() {
    return 2.5;
}

Tea::Tea(): Beverage("Tea") {
}

double Tea::price() {
    return 1.5;
}

BeverageWithMilk::BeverageWithMilk(Beverage* beverage, int milkCount) {
    this->beverage = beverage;
    this->milkCount = milkCount;
}

double BeverageWithMilk::price() {
    return this->beverage->price() + 0.5 * this->milkCount;
}

void BeverageWithMilk::print() {
    this->beverage->print();
    std::cout<<" and " << this->milkCount << " portions of milk, for a total price of " << std::to_string(this->price());
}

BeverageWithMilk::~BeverageWithMilk() {
    delete this->beverage;
}

void BeverageMachine::prepare(const std::string& beverageType, int milkCount) {
    if (beverageType == "Tea") {
        auto* beverage = new Tea();
        if (milkCount == 0) {
            beverage->print();
            delete beverage;
        } else {
            auto beverageWithMilk = BeverageWithMilk(beverage, milkCount);
            beverageWithMilk.print();
        }
        std::cout <<"\n";
    }
    if (beverageType == "Coffee") {
        auto * beverage = new Coffee();
        if (milkCount == 0) {
            beverage->print();
            delete beverage;
        } else {
            auto beverageWithMilk = BeverageWithMilk(beverage, milkCount);
            beverageWithMilk.print();
        }
        std::cout << "\n";
    }
}
