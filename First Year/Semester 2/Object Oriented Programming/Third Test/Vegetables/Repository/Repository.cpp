//
// Created by selen on 22/05/2021.
//

#include <fstream>
#include "Repository.h"

Repository::Repository(std::string &filename, std::vector<Vegetable> &repo) {
    this->vegetables = repo;
    this->filename = filename;
    this->readFromFile();
}

void Repository::add(const Vegetable &vegetable) {
    std::vector<Vegetable>::iterator found;
    found = std::find(this->vegetables.begin(), this->vegetables.end(), vegetable);
    if (found == this->vegetables.end())
        this->vegetables.push_back(vegetable);
    else
        throw RepositoryException((std::string &) "Vegetable already added!\n");
    this->writeToFile();
}

void Repository::remove(const Vegetable &vegetable) {
    std::vector<Vegetable>::iterator found;
    found = std::find(this->vegetables.begin(), this->vegetables.end(), vegetable);
    if (found == this->vegetables.end())
        throw RepositoryException((std::string &) "Vegetable does not exist!\n");
    else
        this->vegetables.erase(found);
    this->writeToFile();
}

void Repository::update(const Vegetable &vegetable) {
    std::vector<Vegetable>::iterator found;
    found = std::find(this->vegetables.begin(), this->vegetables.end(), vegetable);
    if (found == this->vegetables.end())
        throw RepositoryException((std::string &) "Vegetable does not exist!\n");
    else {
        this->vegetables.erase(found);
        this->vegetables.push_back(vegetable);
    }
    this->writeToFile();
}

int Repository::getNumberOfElements() {
    return this->vegetables.size();
}

std::vector<Vegetable> Repository::getAll() {
    return this->vegetables;
}

void Repository::readFromFile() {
    std::ifstream inputFile(this->filename);
    this->vegetables.clear();
    Vegetable currentVegetable;
    while (inputFile >> currentVegetable)
        this->vegetables.push_back(currentVegetable);
    inputFile.close();
}

void Repository::writeToFile() {
    std::ofstream outputFile(this->filename, std::ios::app);
    for (auto& task: this->vegetables)
        outputFile << task;
    outputFile.close();
}

Repository::~Repository() = default;
