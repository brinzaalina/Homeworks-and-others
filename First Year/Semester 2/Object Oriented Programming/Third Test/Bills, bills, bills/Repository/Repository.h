//
// Created by selen on 19/05/2021.
//

#pragma once
#include <vector>
#include <algorithm>
#include "Domain.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>


class Repository{
protected:
    std::vector<Bill> entities;
    std::string inputFile;

public:
    Repository(std::vector<Bill>& repo, std::string& fileName);
    void readFromFile();
    void writeToFile();
    void add(const Bill& bill);
    void deleteElement(const Bill& bill);
    void update(const Bill& bill);
    int getNrElements();
    std::vector<Bill> getAll();
     ~Repository() = default;
};







