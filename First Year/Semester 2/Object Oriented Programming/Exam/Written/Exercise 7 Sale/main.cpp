//
// Created by selen on 18/06/2021.
//

#include <iostream>
#include "classes.h"

int main() {
    Sale sale{};
    SaleItem item1{11, 100};
    SaleItem item2{90, 600};
    SaleItem item3{43, 240};
    sale.add(item1);
    sale.add(item2);
    sale.add(item3);

    auto discount1 = new ItemDiscount(11, 10);
    auto discount2 = new ItemDiscount(90, 10);
    auto discount3 = new ItemDiscount(43, 15);

    SumDiscount all{};
    all.add(discount1);
    all.add(discount2);
    all.add(discount3);

    std::cout << all.calc(sale);
    return 0;
}