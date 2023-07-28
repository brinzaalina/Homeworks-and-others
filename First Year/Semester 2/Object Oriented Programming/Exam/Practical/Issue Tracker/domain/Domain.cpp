//
// Created by selen on 19/06/2021.
//

#include "Domain.h"


std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

User::User(std::string name, std::string type) {
    this->name = std::move(name);
    this->type = std::move(type);
}

std::string User::getName() const {
    return this->name;
}

std::string User::getType() const {
    return this->type;
}

std::istream &operator>>(std::istream &inputStream, User &user) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    user.name = tokens[0];
    user.type = tokens[1];
    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const User &user) {
    outputStream << user.name << "," << user.type;
    return outputStream;
}

bool User::operator==(const User &otherUser) const {
    return (this->getName() == otherUser.name && this->getType() == otherUser.type);
}


Issue::Issue(std::string description, std::string status, std::string reporter, std::string solver) {
    this->description = std::move(description);
    this->status = std::move(status);
    this->reporter = std::move(reporter);
    this->solver = std::move(solver);
}

std::string Issue::getDescription() const {
    return this->description;
}

void Issue::setDescription(std::string newDescription) {
    this->description = std::move(newDescription);
}

std::string Issue::getStatus() const {
    return this->status;
}

void Issue::setStatus(std::string newStatus) {
    this->status = std::move(newStatus);
}

std::string Issue::getReporter() const {
    return this->reporter;
}

void Issue::setReporter(std::string newReporter) {
    this->reporter = std::move(newReporter);
}

std::string Issue::getSolver() const {
    return this->solver;
}

void Issue::setSolver(std::string newSolver) {
    this->solver = std::move(newSolver);
}

std::istream &operator>>(std::istream &inputStream, Issue &issue) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    issue.description = tokens[0];
    issue.status = tokens[1];
    issue.reporter = tokens[2];
    issue.solver = tokens[3];
    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Issue &issue) {
    outputStream << issue.getDescription() << "," << issue.getStatus() << "," << issue.getReporter() << "," << issue.getSolver();
    return outputStream;
}

bool Issue::operator==(const Issue &otherIssue) const {
    return this->getDescription() == otherIssue.getDescription();
}
