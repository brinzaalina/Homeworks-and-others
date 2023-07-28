#include "Domain.h"

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

Programmer::Programmer(std::string name, int revisedFiles, int total) {
    this->name = std::move(name);
    this->revisedFiles = revisedFiles;
    this->total = total;
}

std::string Programmer::getName() const {
    return this->name;
}

int Programmer::getRevisedFiles() const {
    return this->revisedFiles;
}

int Programmer::getTotal() const {
    return this->total;
}

void Programmer::setRevisedFiles(int number) {
    this->revisedFiles += number;
}

std::istream &operator>>(std::istream &inputStream, Programmer &programmer) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    programmer.name = tokens[0];
    programmer.revisedFiles = std::stoi(tokens[1]);
    programmer.total = std::stoi(tokens[2]);
    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Programmer &programmer) {
    outputStream << programmer.name << "," << std::to_string(programmer.revisedFiles) << "," << std::to_string(programmer.total);
    return outputStream;
}

bool Programmer::operator==(const Programmer &otherProgrammer) const {
    return this->getName() == otherProgrammer.getName();
}

SourceFile::SourceFile(std::string name1, std::string status1, std::string creator1, std::string reviser1) {
    this->name = std::move(name1);
    this->status = std::move(status1);
    this->creator = std::move(creator1);
    this->reviser = std::move(reviser1);
}

std::string SourceFile::getName() const {
    return this->name;
}

std::string SourceFile::getStatus() const {
    return this->status;
}

void SourceFile::setStatus(std::string newStatus) {
    this->status = std::move(newStatus);
}

std::string SourceFile::getCreator() const {
    return this->creator;
}

void SourceFile::setCreator(std::string newCreator) {
    this->creator = std::move(newCreator);
}

std::string SourceFile::getReviser() const {
    return this->reviser;
}

void SourceFile::setReviser(std::string newReviser) {
    this->reviser = std::move(newReviser);
}

bool SourceFile::operator==(const SourceFile &file) const {
    return this->name == file.name;
}

std::istream &operator>>(std::istream &inputStream, SourceFile &sourceFile) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    sourceFile.name = tokens[0];
    sourceFile.status = tokens[1];
    sourceFile.creator = tokens[2];
    sourceFile.reviser = tokens[3];
    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const SourceFile &sourceFile) {
    outputStream << sourceFile.getName() << "," << sourceFile.getStatus() << "," << sourceFile.getCreator() << "," << sourceFile.getReviser();
    return outputStream;
}
