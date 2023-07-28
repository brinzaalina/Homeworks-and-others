//
// Created by selen on 21/05/2021.
//

#include <fstream>
#include "Repository.h"

Repository::Repository(std::string &filename, std::vector<Task>& repo) {
    this->tasks = repo;
    this->filename = filename;
    this->readFromFile();
}

void Repository::add(const Task &task) {
    std::vector<Task>::iterator found;
    found = std::find(this->tasks.begin(), this->tasks.end(), task);
    if (found == this->tasks.end())
        this->tasks.push_back(task);
    else
        throw RepositoryException((std::string &) "Task already added!\n");
    this->writeToFile();
}

void Repository::remove(const Task &task) {
    std::vector<Task>::iterator found;
    found = std::find(this->tasks.begin(), this->tasks.end(), task);
    if (found == this->tasks.end())
        throw RepositoryException((std::string &) "Task does not exist!\n");
    else
        this->tasks.erase(found);
    this->writeToFile();
}

void Repository::update(const Task &task) {
    std::vector<Task>::iterator found;
    found = std::find(this->tasks.begin(), this->tasks.end(), task);
    if (found == this->tasks.end())
        throw RepositoryException((std::string &) "Task does not exist!\n");
    else {
        this->tasks.erase(found);
        this->tasks.push_back(task);
    }
    this->writeToFile();
}

int Repository::getNumberOfElements() {
    return this->tasks.size();
}

std::vector<Task> Repository::getAll() {
    return this->tasks;
}

void Repository::readFromFile() {
    std::ifstream inputFile(this->filename);
    this->tasks.clear();
    Task currentTask;
    while (inputFile >> currentTask)
        this->tasks.push_back(currentTask);
    inputFile.close();
}

void Repository::writeToFile() {
    std::ofstream outputFile(this->filename, std::ios::app);
    for (auto& task: this->tasks)
        outputFile << task;
    outputFile.close();
}

Repository::~Repository() = default;
