#pragma once

#include <Observer.h>
#include <Repository.h>

class Service: public Subject {
private:
    Repository& repository;
public:
    Service(Repository& repo);
    ~Service() = default;

    std::vector<Star> getAllStars();
    std::vector<Astronomer> getAllAstronomers();
    void addStar(const std::string& name, const std::string& constellation, int RA, int Dec, int diameter);

    std::vector<Star> getFiltered(std::string filter);
};