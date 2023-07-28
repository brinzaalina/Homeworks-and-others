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
    std::vector<Task> getAllElements();
    int getDurationByPriority(int priority);
    ~Service();
};