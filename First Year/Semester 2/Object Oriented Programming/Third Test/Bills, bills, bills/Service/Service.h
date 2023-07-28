//
// Created by selen on 19/05/2021.
//

#pragma once
#include "Repository.h"
#include "Domain.h"
#include <string>
#include <vector>
#include <string>

class Service{
private:
    Repository& repository;

public:
    Service(Repository& repositoryNew);
    ~Service() = default;

    std::vector<Bill> getAllElements();
    float getUnpaidBillsTotal(std::string& company);
};
