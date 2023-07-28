//
// Created by selen on 18/06/2021.
//

#include "classes.h"

int SaleItem::getCode() const {
    return this->code;
}

double SaleItem::getPrice() const {
    return this->price;
}

SaleItem::SaleItem(int code, double price) {
    this->code = code;
    this->price = price;
}

void Sale::add(SaleItem item) {
    this->push_back(item);
}

ItemDiscount::ItemDiscount(int code, int percentage) {
    this->code = code;
    this->percentage = percentage;
}

double ItemDiscount::calc(const Sale &sale) {
    double discount = 0;
    for (auto& element: sale)
        if (element.getCode() == this->code)
            discount = element.getPrice() * this->percentage / 100;
    return discount;
}

void SumDiscount::add(Discount *discount) {
    this->discounts.push_back(discount);
}

double SumDiscount::calc(const Sale &sale) {
    double total = 0;
    for (auto discount: this->discounts)
        total += discount->calc(sale);
    return total;
}
