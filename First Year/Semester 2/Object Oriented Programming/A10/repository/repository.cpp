#include "repository.h"
#include <algorithm>
#include <fstream>

RepositoryException::RepositoryException(std::string &_message) : message(_message){}

const char* RepositoryException::what() const noexcept {
    return message.c_str();
}

Repository::Repository(std::vector<Dog>& repo_vector, std::string& dog_filename) {
    this->adminRepositoryVector = repo_vector;
    this->dogsFilename = dog_filename;
}

void Repository::loadDogsFromFile() {
    if (!this->dogsFilename.empty()) {
        Dog dogFromFile;
        std::ifstream fin(this->dogsFilename);
        while (fin >> dogFromFile) {
            if (std::find(this->adminRepositoryVector.begin(), this->adminRepositoryVector.end(), dogFromFile) ==
                this->adminRepositoryVector.end())
                this->adminRepositoryVector.push_back(dogFromFile);
        }
        fin.close();
    }
}

void Repository::writeDogsToFile() {
    if (!this->dogsFilename.empty()) {
        std::ofstream fout(this->dogsFilename);
        for (const Dog &dog: this->adminRepositoryVector) {
            fout << dog << "\n";
        }
        fout.close();
    }
}

void Repository::initialiseRepo() {
    this->loadDogsFromFile();
}

std::vector<Dog>& Repository::getAllRepo() {
    return this->adminRepositoryVector;
}

unsigned int Repository::getNrElems() {
    if (this->adminRepositoryVector.empty()) {
        std::string error;
        error += std::string("The database is empty!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    return this->adminRepositoryVector.size();
}

unsigned int Repository::getCap() {
    return this->adminRepositoryVector.capacity();
}

void Repository::addRepo(const Dog& dog) {
    int existing = this->findByName(dog.nameGetter());
    if (existing != -1) {
        std::string error;
        error += std::string("The dog already exists!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->adminRepositoryVector.push_back(dog);
    this->writeDogsToFile();
}

int Repository::findByName(const std::string& name) {
    int searched_index = -1;
    std::vector<Dog>::iterator it;
    it = std::find_if(this->adminRepositoryVector.begin(), this->adminRepositoryVector.end(), [&name](Dog& dog) {return dog.nameGetter() == name;});
    if (it != this->adminRepositoryVector.end())
    {
        searched_index = it - this->adminRepositoryVector.begin();
    }
    return searched_index;
}

void Repository::deleteRepo(int delete_index) {
    if (delete_index == -1) {
        std::string error;
        error += std::string("The dog does not exist!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->adminRepositoryVector.erase(this->adminRepositoryVector.begin() + delete_index);
    this->writeDogsToFile();
}

void Repository::updateRepo(int update_index, const Dog& new_dog) {
    if (update_index == -1) {
        std::string error;
        error += std::string("The dog does not exist!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->adminRepositoryVector[update_index] = new_dog;
    this->writeDogsToFile();
}

Repository::~Repository() = default;