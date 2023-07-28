#include "Repository.h"

#include <utility>

Repository::Repository(std::string programmerFile, std::string sourceFile) {
    this->programmersFile = std::move(programmerFile);
    this->sourcesFile = std::move(sourceFile);
    this->readProgrammersFromFile();
    this->readSourcesFromFile();
}

void Repository::readProgrammersFromFile() {
    if (!this->programmersFile.empty()) {
        Programmer programmer;
        std::ifstream fin(this->programmersFile);
        while (fin >> programmer) {
            if (std::find(this->programmers.begin(), this->programmers.end(), programmer) == this->programmers.end()) {
                this->programmers.push_back(programmer);
            }
        }
        fin.close();
    }
}

void Repository::readSourcesFromFile() {
    if (!this->sourcesFile.empty()) {
        SourceFile source{};
        std::ifstream fin(this->sourcesFile);
        while (fin >> source) {
            if (std::find(this->files.begin(), this->files.end(), source) == this->files.end()) {
                this->files.push_back(source);
            }
        }
        fin.close();
    }
}

void Repository::writeToFile() {
    if (!this->files.empty()) {
        std::ofstream fout(this->sourcesFile);
        for (SourceFile& file: this->files) {
            fout << file << "\n";
        }
        fout.close();
    }
}

void Repository::addSource(const SourceFile &source) {
    if (std::find(this->files.begin(), this->files.end(), source) == this->files.end()) {
        this->files.push_back(source);
        this->writeToFile();
    } else {
        throw RepositoryException("Source file already added!");
    }
}

void Repository::removeSource(const SourceFile &source) {
    std::vector<SourceFile>::iterator found;
    found = std::find(this->files.begin(), this->files.end(), source);
    if (found != this->files.end()) {
        this->files.erase(found);
        this->writeToFile();
    } else {
        throw RepositoryException("Source file does not exist!");
    }
}

void Repository::updateSource(const SourceFile &source) {
    std::vector<SourceFile>::iterator it;
    it = std::find_if(this->files.begin(), this->files.end(), [&source](SourceFile& file) {return
            source.getName() == file.getName(); });
    if (it != this->files.end()) {
        this->files[it - this->files.begin()] = source;
        this->writeToFile();
        for (auto& programmer: this->programmers) {
            if (programmer.getName() == source.getReviser()) {
                programmer.setRevisedFiles(1);
            }
        }
    } else {
        throw RepositoryException("Source file does not exist!");
    }
}

std::vector<Programmer> Repository::getAllProgrammers() {
    return this->programmers;
}

std::vector<SourceFile> Repository::getAllSources() {
    return this->files;
}
