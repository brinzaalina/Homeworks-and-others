//
// Created by selen on 21/05/2021.
//

#include "Service.h"

Service::Service(Repository &repository): repository{repository} {
}

std::vector<Product> Service::getAllElements() {
    return this->repository.getAll();
}

void Service::remove(const std::string &name) {
    Product& product = this->repository.findByName(name);
    this->repository.remove(product);
}

std::vector<Product> Service::getAllFromCategory(const std::string &category) {
    std::vector<Product> products;
    products = this->repository.getAll();
    std::vector<Product> validProducts;
    std::copy_if(products.begin(), products.end(), std::back_inserter(validProducts), [&category](Product& product) { return product.getCategory() == category; });
    return validProducts;
}

Service::~Service() = default;
