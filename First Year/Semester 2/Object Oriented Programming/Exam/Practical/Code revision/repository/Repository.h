#pragma once

#include <string>
#include <Domain.h>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <Exceptions.h>

class Repository {
private:
    std::vector<Programmer> programmers;
    std::vector<SourceFile> files;
    std::string programmersFile;
    std::string sourcesFile;
public:
    explicit Repository(std::string programmerFile, std::string sourceFile);
    void readProgrammersFromFile();
    void readSourcesFromFile();
    void writeToFile();

    void addSource(const SourceFile &source);
    void removeSource(const SourceFile &source);
    void updateSource(const SourceFile &source);

    std::vector<Programmer> getAllProgrammers();
    std::vector<SourceFile> getAllSources();

    ~Repository() = default;
};
