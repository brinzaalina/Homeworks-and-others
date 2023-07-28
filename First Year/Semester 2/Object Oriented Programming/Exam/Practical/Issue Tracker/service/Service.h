//
// Created by selen on 19/06/2021.
//

#pragma once

#include <Observer.h>
#include <Repository.h>

class Service: public Subject {
private:
    Repository& repository;
public:
    explicit Service(Repository& repo): repository{ repo } {};
    std::vector<User> getAllUsers();
    std::vector<Issue> getAllIssues();
    void addIssue(std::string description, std::string reporter);
    void removeIssue(const std::string& description);
    void updateIssue(const std::string& description, const std::string& solver);
};
