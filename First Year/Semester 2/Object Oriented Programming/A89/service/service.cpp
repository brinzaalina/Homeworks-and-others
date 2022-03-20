#include "service.h"
#include <iterator>
#include <algorithm>

Service::Service(Repository& repo): repository(repo) {
}

std::vector<Dog> Service::getAllService() {
    return this->repository.getAllRepo();
}

unsigned int Service::getNrElemsService() {
    return this->repository.getNrElems();
}

unsigned int Service::getCapService() {
    return this->repository.getCap();
}

void Service::addService(const std::string& breed, const std::string& name, int age, const std::string& photograph) {
    Dog dog = Dog(breed, name, age, photograph);
    this->repository.addRepo(dog);
}

void Service::deleteService(const std::string& name) {
    int delete_index = this->repository.findByName(name);
    this->repository.deleteRepo(delete_index);
}

void Service::updateService(const std::string& old_name, const std::string& new_breed, const std::string& new_name, int new_age,const std::string& new_photo) {
    int update_index = this->repository.findByName(old_name);
    Dog new_dog = Dog(new_breed, new_name, new_age, new_photo);
    this->repository.updateRepo(update_index, new_dog);
}

void Service::getFiltered(std::vector<Dog>& valid_dogs, const std::string& filter_string, int age_filter) {
    std::vector<Dog> data;
    data = this->repository.getAllRepo();
    if (filter_string[0] == '\0') {
        std::copy_if(data.begin(), data.end(), std::back_inserter(valid_dogs),[&age_filter](Dog& dog) { return dog.ageGetter() < age_filter; });
    }
    else {
        std::copy_if(data.begin(), data.end(), std::back_inserter(valid_dogs),[&age_filter, &filter_string](Dog& dog) { return dog.ageGetter() < age_filter && dog.breedGetter() == filter_string; });
    }
}

int Service::findByNameService(const std::string& name) {
    return this->repository.findByName(name);
}

std::vector<std::string> Service::getAllBreeds() {
    std::vector<std::string> breeds;
    std::vector<Dog> data;
    data = this->repository.getAllRepo();
    for (const Dog& dog: data) {
        if (std::find(breeds.begin(), breeds.end(), dog.breedGetter()) == breeds.end())
            breeds.push_back(dog.breedGetter());
    }
    return breeds;
}

int Service::numberOfDogsPerBreed(const std::string& breed) {
    int count = 0;
    std::vector<Dog> data;
    data = this->repository.getAllRepo();
    for (const Dog& dog: data) {
        if (dog.breedGetter() == breed) {
            count += 1;
        }
    }
    return count;
}


Service::~Service() = default;