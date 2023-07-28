//
// Created by selen on 19/05/2021.
//

#include "Service.h"
#include <iostream>
Service::Service(Repository &repositoryNew): repository{repositoryNew} {
}

std::vector<Bill> Service::getAllElements(){
    return this->repository.getAll();
}

float Service::getUnpaidBillsTotal(std::string& company){
    std::vector<Bill> allBills = this->getAllElements();
    float total = 0;
    for (auto& bill : allBills)
        if (bill.getCompanyName() == company && !bill.getIsPaid())
            total += bill.getSum();
    return total;
}


