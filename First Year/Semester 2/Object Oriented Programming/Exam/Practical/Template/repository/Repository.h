#pragma once

#include <string>
#include <Domain.h>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <Exceptions.h>

class Repository {
private:
public:
    explicit Repository() = default;
    void readFromFile();
    void writeToFile();

    void addObject(const Object& object);
    void removeObject(const Object& object);
    void updateObject(const Object& object);

    ~Repository() = default;
};
