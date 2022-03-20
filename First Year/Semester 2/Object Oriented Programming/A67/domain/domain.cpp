#include <utility>
#include <vector>
#include <sstream>
#include "domain.h"

Dog::Dog(std::string breed, std::string name, int age, std::string photograph) {
    if (age < 0) {
        throw "Age can't be smaller than 0!";
    }
    this->breed = std::move(breed);
    this->name = std::move(name);
    this->age = age;
    this->photograph = std::move(photograph);
}

std::string Dog::breedGetter() const {
    return this->breed;
}

std::string Dog::nameGetter() const {
    return this->name;
}

int Dog::ageGetter() const {
    return this->age;
}

std::string Dog::photoGetter() const{
    return this->photograph;
}

Dog::~Dog() = default;

std::string Dog::toString() const {
    auto str_age = std::to_string(this->age);
    return "Breed: " + this->breed + " | Name: " + this->name + " | Age: " + str_age + " | Photograph link: " + this->photograph;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

bool Dog::operator==(const Dog& dogToCheck) const {
    return this->name == dogToCheck.name;
}

std::istream& operator>>(std::istream& inputStream, Dog& dog) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    dog.breed = tokens[0];
    dog.name = tokens[1];
    dog.age = std::stoi(tokens[2]);
    dog.photograph = tokens[3];
    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Dog& dogOutput) {
    outputStream << dogOutput.breed << "," << dogOutput.name << "," << std::to_string(dogOutput.age) << "," << dogOutput.photograph;
    return outputStream;
}




