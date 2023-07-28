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
    void remove(const std::string& name);
    std::vector<Product> getAllElements();
    std::vector<Product> getAllFromCategory(const std::string& category);
    ~Service();
};