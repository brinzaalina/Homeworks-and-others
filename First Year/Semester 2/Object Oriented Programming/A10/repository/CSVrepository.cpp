//
// Created by selen on 17/04/2021.
//

#include <fstream>
#include <algorithm>
#include "CSVrepository.h"
#include "repository.h"

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

void CSVRepo::deleteUserRepo(const Dog &dog) {
    int index = this->findByName(dog.nameGetter());
    if (index == -1) {
        std::string error;
        error += std::string("The dog does not exist!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->adoptionList.erase(this->adoptionList.begin() + index);
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

int CSVRepo::findByName(const std::string &name) {
    int searched_index = -1;
    std::vector<Dog>::iterator it;
    it = std::find_if(this->adoptionList.begin(), this->adoptionList.end(), [&name](Dog& dog) {return dog.nameGetter() == name;});
    if (it != this->adoptionList.end())
    {
        searched_index = it - this->adoptionList.begin();
    }
    return searched_index;
}

CSVRepo::~CSVRepo()=default;
