//
// Created by selen on 19/05/2021.
//

#include "Repository.h"

Repository::Repository(std::vector<Bill> &repo, std::string &fileName) {
    this->entities = repo;
    this->inputFile = fileName;
    this->readFromFile();
}

void Repository::readFromFile()
{
    this->entities.clear();
    Bill currentTape;
    std::ifstream fileIn(this->inputFile);
    while (fileIn >> currentTape){
        this->entities.push_back(currentTape);
    }
    fileIn.close();
}

void Repository::writeToFile(){
    std::ofstream fileOut(this->inputFile, std::ios::in);
    for (auto& element : this->entities)
        fileOut << element << "\n";
    fileOut.close();
}

void Repository::add(const Bill& tape){
    std::vector<Bill>::iterator found;
    found = std::find(this->entities.begin(), this->entities.end(), tape);
    if (found == this->entities.end()){
        this->entities.push_back(tape);
    }
    else{
        throw RepositoryException((std::string &) "Tape already added!\n");
    }
    this->writeToFile();
}

void Repository::deleteElement(const Bill& tape){
    std::vector<Bill>::iterator found;
    found = std::find(this->entities.begin(), this->entities.end(), tape);
    if (found == this->entities.end()){
        throw RepositoryException((std::string &) "Tape does not exist!\n");
    }
    else{
        this->entities.erase(found);
    }
    this->writeToFile();
}

void Repository::update(const Bill& tape){
    std::vector<Bill>::iterator found;
    found = std::find(this->entities.begin(), this->entities.end(), tape);
    if (found == this->entities.end()){
        throw RepositoryException((std::string &) "Tape does not exist!\n");
    }
    else{
        this->entities.erase(found);
        this->entities.push_back(tape);
    }
    this->writeToFile();
}

int Repository::getNrElements(){
    return this->entities.size();
}

std::vector<Bill> Repository::getAll(){
    return this->entities;
}
