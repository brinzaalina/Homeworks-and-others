//
// Created by selen on 19/06/2021.
//

#pragma once

#include <vector>
#include <Domain.h>
#include <fstream>
#include <algorithm>
#include <Exceptions.h>

class Repository {
private:
    std::vector<User> users;
    std::vector<Issue> issues;
    std::string usersFile;
    std::string issuesFile;
public:
    Repository(std::string usersFile, std::string issuesFile);
    void readUsersFromFile();
    void readIssuesFromFile();
    void writeIssuesToFile();
    void addIssue(const Issue& issue);
    void removeIssue(const Issue& issue);
    void updateIssue(const Issue& issue);
    std::vector<User> getAllUsers();
    std::vector<Issue> getAllIssues();
    ~Repository() = default;
};
