//
// Created by selen on 19/06/2021.
//

#include "Service.h"

#include <utility>

std::vector<User> Service::getAllUsers() {
    return this->repository.getAllUsers();
}

std::vector<Issue> Service::getAllIssues() {
    std::vector<Issue> issues = this->repository.getAllIssues();
    for (int i = 0; i < issues.size() - 1; i++)
        for (int j = i + 1; j < issues.size(); j++)
            if (issues[i].getStatus() == issues[j].getStatus()) {
                if (issues[i].getDescription() > issues[j].getDescription())
                    std::swap(issues[i], issues[j]);
            } else if (issues[i].getStatus() < issues[j].getStatus())
                std::swap(issues[i], issues[j]);
    return issues;
}

void Service::addIssue(std::string description, std::string reporter) {
    if (description.empty())
        throw ServiceException("The description is empty!");
    Issue newIssue{std::move(description), "open", std::move(reporter), "no solver"};
    this->repository.addIssue(newIssue);
    this->notify();
}

void Service::removeIssue(const std::string& description) {
    std::vector<Issue> issues = this->repository.getAllIssues();
    for (auto& issue: issues)
        if (issue.getDescription() == description) {
            if (issue.getStatus() == "closed") {
                Issue issueToDelete{ description, "closed", issue.getReporter(), issue.getSolver()};
                this->repository.removeIssue(issueToDelete);
                this->notify();
            } else {
                throw ServiceException("The issue is opened!");
            }
        }
}

void Service::updateIssue(const std::string& description, const std::string& solver) {
    std::vector<Issue> issues = this->repository.getAllIssues();
    for (auto& issue: issues)
        if (issue.getDescription() == description) {
            if (issue.getStatus() == "open") {
                Issue issueToUpdate{ description, "closed", issue.getReporter(), solver};
                this->repository.updateIssue(issueToUpdate);
                this->notify();
            } else {
                throw ServiceException("The issue is already closed!");
            }
        }
}
