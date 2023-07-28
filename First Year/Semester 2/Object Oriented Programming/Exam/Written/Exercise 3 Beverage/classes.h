#pragma once
#include <iostream>
#include <memory>

class Beverage {
private:
    std::string description;
public:
    std::string getDescription();
    Beverage() = default;
    explicit Beverage(std::string description);
    virtual double price() = 0;
    virtual void print();
    virtual ~Beverage();
};

class Coffee: public Beverage {
public:
    Coffee();
    double price() override;
};

class Tea: public Beverage {
public:
    Tea();
    double price() override;
};

class BeverageWithMilk: public Beverage{
private:
    Beverage* beverage;
    int milkCount;
public:
    explicit BeverageWithMilk(Beverage* beverage, int milkCount);
    double price() override;
    void print() override;
    ~BeverageWithMilk() override;
};

class BeverageMachine {
public:
    BeverageMachine()=default;
    void prepare(const std::string& beverageType, int milkCount);
};