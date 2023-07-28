//
// Created by selen on 19/06/2021.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

class User {
private:
    std::string name;
    std::string type;
public:
    User() = default;
    User(std::string name, std::string type);
    std::string getName() const;
    std::string getType() const;
    ~ User() = default;

    friend std::istream& operator>>(std::istream& inputStream, User& user);

    friend std::ostream& operator<<(std::ostream& outputStream, const User& user);

    bool operator==(const User& otherUser) const;
};

class Issue {
private:
    std::string description;
    std::string status;
    std::string reporter;
    std::string solver;
public:
    Issue() = default;
    Issue(std::string description, std::string status, std::string reporter, std::string solver);

    std::string getDescription() const;
    void setDescription(std::string newDescription);

    std::string getStatus() const;
    void setStatus(std::string newStatus);

    std::string getReporter() const;
    void setReporter(std::string newReporter);

    std::string getSolver() const;
    void setSolver(std::string newSolver);

    ~Issue() = default;

    friend std::istream& operator>>(std::istream& inputStream, Issue& issue);

    friend std::ostream& operator<<(std::ostream& outputStream, const Issue& issue);

    bool operator==(const Issue& otherIssue) const;
};