//
// Created by selen on 21/06/2021.
//

#include <fstream>
#include <algorithm>
#include <Exceptions.h>
#include "Repository.h"

Repository::Repository(std::string astronomersFile, std::string starsFile) {
    this->astronomersFile = std::move(astronomersFile);
    this->starsFile = std::move(starsFile);
    this->loadAstronomers();
    this->readStarsFromFile();
}

void Repository::loadAstronomers() {
    if (!this->astronomersFile.empty()) {
        Astronomer astronomer;
        std::ifstream fin(this->astronomersFile);
        while (fin >> astronomer) {
            if (std::find(this->astronomers.begin(), this->astronomers.end(), astronomer) == this->astronomers.end()) {
                this->astronomers.push_back(astronomer);
            }
        }
        fin.close();
    }
}

void Repository::readStarsFromFile() {
    if (!this->starsFile.empty()) {
        Star star;
        std::ifstream fin(this->starsFile);
        while (fin >> star) {
            if (std::find(this->stars.begin(), this->stars.end(), star) == this->stars.end()) {
                this->stars.push_back(star);
            }
        }
        fin.close();
    }
}

void Repository::writeStarsToFile() {
    if (!this->stars.empty()) {
        std::ofstream fout(this->starsFile);
        for (Star& star: this->stars) {
            fout << star << "\n";
        }
        fout.close();
    }
}

void Repository::addStar(const Star &star) {
    if (std::find(this->stars.begin(), this->stars.end(), star) == this->stars.end()) {
        this->stars.push_back(star);
        this->writeStarsToFile();
    } else {
        throw RepositoryException("Source file already added!");
    }
}

std::vector<Astronomer> Repository::getAllAstronomers() {
    return this->astronomers;
}

std::vector<Star> Repository::getAllStars() {
    return this->stars;
}
