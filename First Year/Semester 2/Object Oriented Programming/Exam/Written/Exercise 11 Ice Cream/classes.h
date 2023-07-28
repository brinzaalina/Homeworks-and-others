//
// Created by selen on 19/06/2021.
//

#pragma once

#include <string>
#include <vector>

class Icecream {
public:
    Icecream() = default;
    virtual std::string getDescription() = 0;
    virtual double computePrice() = 0;
    virtual ~Icecream() = default;
};

class SimpleIcecream: public Icecream {
private:
    std::string description;
    double price;
public:
    SimpleIcecream(std::string& description, double price);
    std::string getDescription() override;
    double computePrice() override;
};

class IcecreamWithTopping: public Icecream {
protected:
    Icecream* icecream;
public:
    explicit IcecreamWithTopping(Icecream* icecream);
    virtual std::string addTopping() = 0;
    ~IcecreamWithTopping() override { delete icecream; }
};

class IcecreamWithChocolateTopping: public IcecreamWithTopping {
public:
    explicit IcecreamWithChocolateTopping(Icecream* icecream);
    std::string addTopping() override;
    std::string getDescription() override;
    double computePrice() override;
};

class IcecreamWithCaramelTopping: public IcecreamWithTopping {
public:
    explicit IcecreamWithCaramelTopping(Icecream* icecream);
    std::string addTopping() override;
    std::string getDescription() override;
    double computePrice() override;
};

class Order {
private:
    std::vector<Icecream*> icecreams;
public:
    Order() = default;
    void addIcecream(Icecream* icecream);
    void printOrder();
    ~Order() { for (auto a: icecreams) delete a;}
};
