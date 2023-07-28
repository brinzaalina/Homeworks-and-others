//
// Created by selen on 21/05/2021.
//

#include "Domain.h"

Product::Product(): quantity(0) {
}

Product::Product(const std::string &categoryOfProduct, const std::string& nameOfProduct, int quantityOfProduct) {
    this->category = categoryOfProduct;
    this->name = nameOfProduct;
    this->quantity = quantityOfProduct;
}

Product::Product(const Product &product) {
    this->category = product.category;
    this->name = product.name;
    this->quantity = product.quantity;
}

std::string Product::getCategory() const {
    return this->category;
}

std::string Product::getName() const {
    return this->name;
}

int Product::getQuantity() const {
    return this->quantity;
}

void Product::setCategory(const std::string &newCategory) {
    this->category = newCategory;
}

void Product::setName(const std::string &newName) {
    this->name = newName;
}

void Product::setQuantity(int newQuantity) {
    this->quantity = newQuantity;
}

std::vector<std::string> Product::tokenize(char delimiter, const std::string &line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &istream, Product &product) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return istream;
    tokens = Product::tokenize('|', line);
    product.category = tokens[0];
    product.name = tokens[1];
    product.quantity = std::stoi(tokens[2]);
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Product &product) {
    ostream << product.getCategory() << "|" << product.getName() << "|" << std::to_string(product.getQuantity()) << "\n";
    return ostream;
}

bool Product::operator==(const Product &product) const {
    return this->name == product.name;
}

Product::~Product() = default;
