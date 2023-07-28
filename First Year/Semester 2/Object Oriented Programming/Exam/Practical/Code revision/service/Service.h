#pragma once

#include <observer/Observer.h>
#include <Repository.h>

class Service: public Subject {
private:
    Repository& repository;
public:
    explicit Service(Repository& repo): repository{ repo } {};
    std::vector<Programmer> getAllProgrammers();
    std::vector<SourceFile> getAllSources();
    void addFile(const std::string &name, const std::string &creator);
    void updateSource(const std::string &name, const std::string &reviser);
};