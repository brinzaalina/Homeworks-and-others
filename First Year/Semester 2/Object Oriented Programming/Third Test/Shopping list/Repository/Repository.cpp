//
// Created by selen on 21/05/2021.
//

#include <fstream>
#include "Repository.h"

Repository::Repository(std::string &filename, std::vector<Product>& repo) {
    this->products = repo;
    this->filename = filename;
    this->readFromFile();
}

void Repository::add(const Product &product) {
    std::vector<Product>::iterator found;
    found = std::find(this->products.begin(), this->products.end(), product);
    if (found == this->products.end())
        this->products.push_back(product);
    else
        throw RepositoryException((std::string &) "Product already added!\n");
    this->writeToFile();
}

void Repository::remove(const Product &product) {
    std::vector<Product>::iterator found;
    found = std::find(this->products.begin(), this->products.end(), product);
    if (found == this->products.end())
        throw RepositoryException((std::string &) "Product does not exist!\n");
    else
        this->products.erase(found);
    this->writeToFile();
}

void Repository::update(const Product &product) {
    std::vector<Product>::iterator found;
    found = std::find(this->products.begin(), this->products.end(), product);
    if (found == this->products.end())
        throw RepositoryException((std::string &) "Product does not exist!\n");
    else {
        this->products.erase(found);
        this->products.push_back(product);
    }
    this->writeToFile();
}

int Repository::getNumberOfElements() {
    return this->products.size();
}

std::vector<Product> Repository::getAll() {
    return this->products;
}

Product& Repository::findByName(const std::string& name) {
    int searched_index = -1;
    std::vector<Product>::iterator it;
    it = std::find_if(this->products.begin(), this->products.end(), [&name](Product& product) {return product.getName() == name;});
    if (it != this->products.end()){
        searched_index = it - this->products.begin();
    } else
        throw RepositoryException((std::string &) "Product does not exist!\n");
    return this->products[searched_index];
}

void Repository::readFromFile() {
    std::ifstream inputFile(this->filename);
    this->products.clear();
    Product product;
    while (inputFile >> product)
        this->products.push_back(product);
    inputFile.close();
}

void Repository::writeToFile() {
    std::ofstream outputFile(this->filename);
    for (auto& product: this->products)
        outputFile << product;
    outputFile.close();
}

Repository::~Repository() = default;
