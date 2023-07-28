//
// Created by selen on 21/05/2021.
//

#include "Service.h"

Service::Service(Repository &repository): repository{repository} {
}

std::vector<Vegetable> Service::getAllElements() {
    return this->repository.getAll();
}

std::vector<std::string> Service::vegetableList(const std::string &family) {
    std::vector<std::string> vegetables;
    std::vector<Vegetable> allVegetables = this->repository.getAll();
    for (auto& vegetable: allVegetables) {
        if (vegetable.getFamily() == family) {
            std::string toAdd;
            toAdd += vegetable.getName() + ": ";
            toAdd += vegetable.getConsumables()[0];
            for (int index = 1; index < vegetable.getConsumables().size(); index++) {
                toAdd += ", ";
                toAdd += vegetable.getConsumables()[index];
            }
            vegetables.push_back(toAdd);
        }
    }
    return vegetables;
}

std::string Service::getConsumables(const std::string &name) {
    std::vector<Vegetable> allVegetables = this->repository.getAll();
    std::string consume;
    for (auto& vegetable: allVegetables) {
        if (vegetable.getName() == name) {
            consume += vegetable.getConsumables()[0];
            for (int index = 1; index < vegetable.getConsumables().size(); index++) {
                consume += ", ";
                consume += vegetable.getConsumables()[index];
            }
        }
    }
    return consume;
}

std::string Service::getFamilyByName(const std::string& name) {
    std::vector<Vegetable> allVegetables = this->repository.getAll();
    std::string fam;
    for (auto& vegetable: allVegetables) {
        if (vegetable.getName() == name)
            fam = vegetable.getFamily();
    }
    return fam;
}

Service::~Service() = default;
