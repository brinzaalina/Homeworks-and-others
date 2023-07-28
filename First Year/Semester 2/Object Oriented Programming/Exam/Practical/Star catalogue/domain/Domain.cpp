//
// Created by selen on 21/06/2021.
//

#include <sstream>
#include "Domain.h"

Star::Star(std::string name, std::string constellation, int RA, int Dec, int diameter) {
    this->name = std::move(name);
    this->constellation = std::move(constellation);
    this->RA = RA;
    this->Dec = Dec;
    this->diameter = diameter;
}

Star::Star(const Star &star) {
    this->name = star.name;
    this->constellation = star.constellation;
    this->RA = star.RA;
    this->Dec = star.Dec;
    this->diameter = star.diameter;
}

bool Star::operator==(const Star &otherStar) const {
    return this->name == otherStar.name;
}

std::string Star::getName() const {
    return this->name;
}

std::string Star::getConstellation() const {
    return this->constellation;
}

int Star::getRA() const {
    return this->RA;
}

int Star::getDec() const {
    return this->Dec;
}

int Star::getDiameter() const {
    return this->diameter;
}

std::vector<std::string> Star::tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &istream, Star &star) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> lineParts;
    if (line.empty()){
        return istream;
    }
    lineParts = Star::tokenize(line, ',');
    star.name = lineParts[0];
    star.constellation = lineParts[1];
    star.RA = std::stoi(lineParts[2]);
    star.Dec = std::stoi(lineParts[3]);
    star.diameter = std::stoi(lineParts[4]);
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Star &star) {
    std::string result;
    result.append(star.getName());
    result.append(",");
    result.append(star.getConstellation());
    result.append(",");
    result.append(std::to_string(star.getRA()));
    result.append(",");
    result.append(std::to_string(star.getDec()));
    result.append(",");
    result.append(std::to_string(star.getDiameter()));
    ostream << result;
    return ostream;
}

Astronomer::Astronomer(std::string name, std::string constellation) {
    this->name = std::move(name);
    this->constellation = std::move(constellation);
}

Astronomer::Astronomer(const Astronomer &astronomer) {
    this->name = astronomer.name;
    this->constellation = astronomer.constellation;
}

bool Astronomer::operator==(const Astronomer &astronomer) const {
    return this->name == astronomer.name;
}

std::string Astronomer::getName() const {
    return this->name;
}

std::string Astronomer::getConstellation() const {
    return this->constellation;
}

std::vector<std::string> Astronomer::tokenize(const std::string &str, char delimiter) {std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &istream, Astronomer &astronomer) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> lineParts;
    if (line == "")
    {
        return istream;
    }
    lineParts = Astronomer::tokenize(line, ',');
    astronomer.name = lineParts[0];
    astronomer.constellation = lineParts[1];
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Astronomer &astronomer) {
    std::string result;
    result.append(astronomer.getName());
    result.append(",");
    result.append(astronomer.getConstellation());
    result.append("\n");
    ostream << result;
    return ostream;
}
