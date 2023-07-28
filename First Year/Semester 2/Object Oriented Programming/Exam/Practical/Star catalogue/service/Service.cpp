//
// Created by selen on 21/06/2021.
//

#include "Service.h"

Service::Service(Repository &repo): repository{repo} {
}

std::vector<Star> Service::getAllStars() {
    return this->repository.getAllStars();
}

std::vector<Astronomer> Service::getAllAstronomers() {
    return this->repository.getAllAstronomers();
}

void Service::addStar(const std::string& name, const std::string& constellation, int RA, int Dec, int diameter) {
    Star star{name, constellation, RA, Dec, diameter};
    this->repository.addStar(star);
    this->notify();
}

std::vector<Star> Service::getFiltered(std::string filter) {
    std::vector<Star> filtered;
    std::vector<Star> allStars = this->repository.getAllStars();

    for (auto & star: allStars) {
        std::string name = star.getName();
        if (std::search(name.begin(), name.end(), filter.begin(), filter.end(), [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2);}) != name.end())
            filtered.push_back(star);
    }
    return filtered;
}
