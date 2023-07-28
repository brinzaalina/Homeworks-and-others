//
// Created by selen on 21/05/2021.
//

#pragma once

#include <Domain.h>
#include <Exceptions.h>
#include <algorithm>

class Repository {
private:
    std::vector<Vegetable> vegetables;
    std::string filename;
public:
    Repository(std::string& filename, std::vector<Vegetable>& repo);
    void add(const Vegetable& vegetable);
    void remove(const Vegetable& vegetable);
    void update(const Vegetable& vegetable);
    int getNumberOfElements();
    std::vector<Vegetable> getAll();
    void readFromFile();
    void writeToFile();
    ~Repository();
};
