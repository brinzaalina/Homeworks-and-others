#include "Service.h"

std::vector<Programmer> Service::getAllProgrammers() {
    return this->repository.getAllProgrammers();
}

void Service::addFile(const std::string &name, const std::string &creator) {
    if (name.empty())
        throw ServiceException("Name is empty!");
    SourceFile source{name, "not revised", creator, "empty"};
    this->repository.addSource(source);
    this->notify();
}

void Service::updateSource(const std::string &name, const std::string &reviser) {
    std::vector<SourceFile> sources = this->repository.getAllSources();
    for (auto& source: sources)
        if (source.getName() == name) {
            if (source.getStatus() == "not revised") {
                if (source.getCreator() == reviser)
                    throw ServiceException("Source file can't be revised by the creator!");
                SourceFile sourceUpdate{name, "revised", source.getCreator(), reviser};
                this->repository.updateSource(sourceUpdate);
                this->notify();
            } else {
                throw ServiceException("The source is already revised!");
            }
        }
}

std::vector<SourceFile> Service::getAllSources() {
    return this->repository.getAllSources();
}




