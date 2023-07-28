#pragma once

#include <vector>
#include "Domain.h"

class Repository {
private:
    std::vector<Astronomer> astronomers;
    std::vector<Star> stars;
    std::string astronomersFile;
    std::string starsFile;
public:
    Repository(std::string astronomersFile, std::string starsFile);
    void loadAstronomers();
    void readStarsFromFile();
    void writeStarsToFile();
    void addStar(const Star& star);

    std::vector<Astronomer> getAllAstronomers();
    std::vector<Star> getAllStars();
};