#include <utility>
#include "domain.h"

Dog::Dog(string breed, string name, int age, string photograph) {
    if (age < 0) {
        throw "Age can't be smaller than 0!";
    }
    this->breed = std::move(breed);
    this->name = std::move(name);
    this->age = age;
    this->photograph = std::move(photograph);
}

string Dog::breedGetter() {
    return this->breed;
}

string Dog::nameGetter() {
    return this->name;
}

int Dog::ageGetter() {
    return this->age;
}

string Dog::photoGetter(){
    return this->photograph;
}

Dog::~Dog() = default;

string Dog::toString() const {
    auto str_age = to_string(this->age);
    return "Breed: " + this->breed + " | Name: " + this->name + " | Age: " + str_age + " | Photograph link: " + this->photograph;
}



