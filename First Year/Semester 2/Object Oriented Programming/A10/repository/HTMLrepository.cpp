//
// Created by selen on 17/04/2021.
//

#include <fstream>
#include <algorithm>
#include "HTMLrepository.h"
#include "repository.h"

HTMLRepo::HTMLRepo(const std::vector<Dog> &adoptionList, const std::string &userFilename) {
    this->adoptionList = adoptionList;
    this->userFilename = userFilename;
}

std::vector<Dog>& HTMLRepo::getAllUserRepo() {
    return this->adoptionList;
}

unsigned int HTMLRepo::getNrElems() {
    return this->adoptionList.size();
}

unsigned int HTMLRepo::getCap() {
    return this->adoptionList.capacity();
}

std::string& HTMLRepo::getFilename() {
    return this->userFilename;
}

void HTMLRepo::addUserRepo(const Dog &dog) {
    this->adoptionList.push_back(dog);
    this->writeToFile();
}

void HTMLRepo::deleteUserRepo(const Dog &dog) {
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

void HTMLRepo::writeToFile() {
    std::ofstream fout(this->userFilename);
    fout << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
    fout << "<table border=\"1\">\n";
    fout << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Link</td></tr>\n";
    for (const Dog& dog: this->adoptionList) {
        fout << "<tr><td>" << dog.breedGetter() << "</td>"
                   << "<td>" << dog.nameGetter() << "</td>"
                   << "<td>" << std::to_string(dog.ageGetter()) << "</td>"
                   << "<td><a href=\"" << dog.photoGetter() << "\">"<<dog.photoGetter()<<"</a></td>" << '\n';
    }
    fout << "</table></body></html>";
    fout.close();
}

int HTMLRepo::findByName(const std::string &name) {
    int searched_index = -1;
    std::vector<Dog>::iterator it;
    it = std::find_if(this->adoptionList.begin(), this->adoptionList.end(), [&name](Dog& dog) {return dog.nameGetter() == name;});
    if (it != this->adoptionList.end())
    {
        searched_index = it - this->adoptionList.begin();
    }
    return searched_index;
}

HTMLRepo::~HTMLRepo()=default;
