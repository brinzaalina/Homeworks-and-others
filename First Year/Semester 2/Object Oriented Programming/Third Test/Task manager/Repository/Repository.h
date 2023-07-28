//
// Created by selen on 21/05/2021.
//

#pragma once

#include <Domain.h>
#include <Exceptions.h>
#include <algorithm>

class Repository {
private:
    std::vector<Task> tasks;
    std::string filename;
public:
    Repository(std::string& filename, std::vector<Task>& repo);
    void add(const Task& task);
    void remove(const Task& task);
    void update(const Task& task);
    int getNumberOfElements();
    std::vector<Task> getAll();
    void readFromFile();
    void writeToFile();
    ~Repository();
};
