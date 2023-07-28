//
// Created by selen on 21/05/2021.
//

#include "Domain.h"

Task::Task(): duration(0), priority(0) {
}

Task::Task(const std::string &description, int duration, int priority) {
    this->description = description;
    this->duration = duration;
    this->priority = priority;
}

Task::Task(const Task &task) {
    this->description = task.description;
    this->duration = task.duration;
    this->priority = task.priority;
}

std::string Task::getDescription() const {
    return this->description;
}

int Task::getDuration() const {
    return this->duration;
}

int Task::getPriority() const {
    return this->priority;
}

void Task::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Task::setDuration(int newDuration) {
    this->duration = newDuration;
}

void Task::setPriority(int newPriority) {
    this->priority = newPriority;
}

std::vector<std::string> Task::tokenize(char delimiter, const std::string &line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &istream, Task &task) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return istream;
    tokens = Task::tokenize('|', line);
    task.description = tokens[0];
    task.duration = std::stoi(tokens[1]);
    task.priority = std::stoi(tokens[2]);
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Task &task) {
    ostream << task.getDescription() << "|" << std::to_string(task.getDuration()) << "|" << std::to_string(task.getPriority()) << "\n";
    return ostream;
}

bool Task::operator==(const Task &otherTask) const {
    return this->description == otherTask.description;
}

Task::~Task() = default;
