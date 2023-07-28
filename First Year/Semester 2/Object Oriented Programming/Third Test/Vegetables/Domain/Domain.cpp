//
// Created by selen on 22/05/2021.
//

#include "Domain.h"

Vegetable::Vegetable() = default;

Vegetable::Vegetable(const std::string &family, const std::string &name, std::vector<std::string> &consumables) {
    this->family = family;
    this->name = name;
    this->consumables = consumables;
}

Vegetable::Vegetable(const Vegetable &vegetable) {
    this->family = vegetable.family;
    this->name = vegetable.name;
    this->consumables = vegetable.consumables;
}

std::string Vegetable::getFamily() const {
    return this->family;
}

std::string Vegetable::getName() const {
    return this->name;
}

std::vector<std::string> Vegetable::getConsumables() {
    return this->consumables;
}

void Vegetable::setFamily(const std::string &newFamily) {
    this->family = newFamily;
}

void Vegetable::setName(const std::string &newName) {
    this->name = newName;
}

void Vegetable::setConsumables(std::vector<std::string>& newConsumables) {
    this->consumables = newConsumables;
}

std::vector<std::string> Vegetable::tokenize(char delimiter, const std::string &line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &istream, Vegetable &vegetable) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return istream;
    tokens = Vegetable::tokenize('|', line);
    vegetable.family = tokens[0];
    vegetable.name = tokens[1];
    std::vector<std::string> consume = Vegetable::tokenize(',', tokens[2]);
    vegetable.consumables = consume;
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Vegetable &vegetable) {
    std::string line;
    line.append(vegetable.family);
    line.append("|");
    line.append(vegetable.name);
    line.append("|");
    line.append(vegetable.consumables[0]);
    for(int index = 1; index < vegetable.consumables.size(); index++){
        line.append(",");
        line.append(vegetable.consumables[index]);
    }
    ostream << line;
    return ostream;
}

bool Vegetable::operator==(const Vegetable &vegetable) const {
    return this->family == vegetable.family && this->name == vegetable.name && this->consumables == vegetable.consumables;
}

Vegetable::~Vegetable() = default;
