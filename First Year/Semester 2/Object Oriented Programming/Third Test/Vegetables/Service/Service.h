//
// Created by selen on 21/05/2021.
//

#pragma once

#include <Repository.h>

class Service {
private:
    Repository& repository;
public:
    explicit Service(Repository& repository);
    std::vector<Vegetable> getAllElements();
    std::vector<std::string> vegetableList(const std::string& family);
    std::string getConsumables(const std::string& name);
    std::string getFamilyByName(const std::string& name);
    ~Service();
};