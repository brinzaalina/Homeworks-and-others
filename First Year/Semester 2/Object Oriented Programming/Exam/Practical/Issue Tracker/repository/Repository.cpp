//
// Created by selen on 19/06/2021.
//

#include "Repository.h"

Repository::Repository(std::string usersFile, std::string issuesFile) {
    this->usersFile = std::move(usersFile);
    this->issuesFile = std::move(issuesFile);
    this->readUsersFromFile();
    this->readIssuesFromFile();
}

void Repository::readUsersFromFile() {
    if (!this->usersFile.empty()) {
        User user;
        std::ifstream fin(this->usersFile);
        while (fin >> user) {
            if (std::find(this->users.begin(), this->users.end(), user) == this->users.end()) {
                this->users.push_back(user);
            }
        }
        fin.close();
    }
}

void Repository::readIssuesFromFile() {
    if (!this->issuesFile.empty()) {
        Issue issue;
        std::ifstream fin(this->issuesFile);
        while (fin >> issue) {
            if (std::find(this->issues.begin(), this->issues.end(), issue) == this->issues.end()) {
                this->issues.push_back(issue);
            }
        }
        fin.close();
    }
}

void Repository::writeIssuesToFile() {
    if (!this->issuesFile.empty()) {
        std::ofstream fout(this->issuesFile);
        for (Issue& issue: this->issues) {
            fout << issue << "\n";
        }
        fout.close();
    }
}

void Repository::addIssue(const Issue &issue) {
    if (std::find(this->issues.begin(), this->issues.end(), issue) == this->issues.end()) {
        this->issues.push_back(issue);
        this->writeIssuesToFile();
    } else {
        throw RepositoryException("Issue already added!");
    }
}

void Repository::removeIssue(const Issue &issue) {
    std::vector<Issue>::iterator found;
    found = std::find(this->issues.begin(), this->issues.end(), issue);
    if (found != this->issues.end()) {
        this->issues.erase(found);
        this->writeIssuesToFile();
    } else {
        throw RepositoryException("Issue does not exist!");
    }
}

void Repository::updateIssue(const Issue &issue) {
    std::vector<Issue>::iterator it;
    it = std::find_if(this->issues.begin(), this->issues.end(), [&issue](Issue& issue1) {return issue.getDescription() == issue1.getDescription(); });
    if (it != this->issues.end()) {
        this->issues[it - this->issues.begin()] = issue;
        this->writeIssuesToFile();
    } else {
        throw RepositoryException("Issue does not exist!");
    }
}

std::vector<User> Repository::getAllUsers() {
    return this->users;
}

std::vector<Issue> Repository::getAllIssues() {
    return this->issues;
}



