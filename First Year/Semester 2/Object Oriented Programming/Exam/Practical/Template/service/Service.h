#pragma once

#include <observer/Observer.h>
#include <Repository.h>

class Service: public Subject {
private:
    Repository& repository;
public:
    explicit Service(Repository& repo): repository{ repo } {};
    void addObject();
    void removeObject();
    void updateObject();
};