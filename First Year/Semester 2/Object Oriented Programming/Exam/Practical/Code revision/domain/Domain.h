#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>

class Programmer {
private:
    std::string name;
    int revisedFiles;
    int total;
public:
    explicit Programmer(std::string = "empty", int revisedFiles = 0, int total = 0);
    std::string getName() const;
    int getRevisedFiles() const;
    int getTotal() const;
    void setRevisedFiles(int number);
    ~Programmer() = default;

    friend std::istream& operator>>(std::istream& inputStream, Programmer& programmer);
    friend std::ostream& operator<<(std::ostream& outputStream, const Programmer& programmer);

    bool operator==(const Programmer& otherProgrammer) const;
};

class SourceFile {
private:
    std::string name;
    std::string status;
    std::string creator;
    std::string reviser;
public:
    explicit SourceFile(std::string name1 = "empty", std::string status1 = "empty", std::string creator1 = "empty", std::string reviser1 = "empty");
    std::string getName() const;
    std::string getStatus() const;
    void setStatus(std::string newStatus);
    std::string getCreator() const;
    void setCreator(std::string newCreator);
    std::string getReviser() const;
    void setReviser(std::string newReviser);
    ~SourceFile() = default;

    friend std::istream& operator>>(std::istream& inputStream, SourceFile& sourceFile);
    friend std::ostream& operator<<(std::ostream& outputStream, const SourceFile& sourceFile);
    bool operator==(const SourceFile& file) const;
};