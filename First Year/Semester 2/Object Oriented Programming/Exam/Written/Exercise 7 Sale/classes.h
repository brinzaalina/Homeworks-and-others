//
// Created by selen on 18/06/2021.
//

#pragma once
#include <vector>

class SaleItem{
private:
    int code;
    double price;
public:
    SaleItem(int code, double price);
    int getCode() const;
    double getPrice() const;
};

class Sale: public std::vector<SaleItem>{
public:
    void add(SaleItem item);
};

class Discount {
public:
    Discount() = default;
    virtual double calc(const Sale &sale) = 0;
};

class ItemDiscount: public Discount {
private:
    int code;
    int percentage;
public:
    ItemDiscount(int code, int percentage);
    double calc(const Sale &sale) override;
};

class SumDiscount: public Discount {
private:
    std::vector<Discount*> discounts;
public:
    SumDiscount() = default;
    void add(Discount* discount);
    double calc(const Sale &sale) override;
};
