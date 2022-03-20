//
// Created by selen on 17/04/2021.
//

#include <fstream>
#include "CSVrepository.h"

CSVRepo::CSVRepo(const std::vector<Dog>& adoptionList, const std::string& userFilename) {
    this->adoptionList = adoptionList;
    this->userFilename = userFilename;
}

std::vector<Dog>& CSVRepo::getAllUserRepo() {
    return this->adoptionList;
}

unsigned int CSVRepo::getNrElems() {
    return this->adoptionList.size();
}

unsigned int CSVRepo::getCap() {
    return this->adoptionList.capacity();
}

std::string& CSVRepo::getFilename() {
    return this->userFilename;
}

void CSVRepo::addUserRepo(const Dog &dog) {
    this->adoptionList.push_back(dog);
    this->writeToFile();
}

void CSVRepo::writeToFile() {
    std::ofstream fout(this->userFilename);
    if (!this->adoptionList.empty()) {
        for (const Dog& dog: this->adoptionList) {
            fout<<dog<<"\n";
        }
    }
    fout.close();
}

CSVRepo::~CSVRepo()=default;
