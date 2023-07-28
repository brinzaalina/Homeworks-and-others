//
// Created by selen on 21/05/2021.
//

#pragma once

#include <Domain.h>
#include <Exceptions.h>
#include <algorithm>

class Repository {
private:
    std::vector<Product> products;
    std::string filename;
public:
    Repository(std::string& filename, std::vector<Product>& repo);
    void add(const Product& product);
    void remove(const Product& product);
    void update(const Product& product);
    int getNumberOfElements();
    std::vector<Product> getAll();
    Product& findByName(const std::string& name);
    void readFromFile();
    void writeToFile();
    ~Repository();
};
