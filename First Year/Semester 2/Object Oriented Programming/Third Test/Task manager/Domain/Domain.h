//
// Created by selen on 21/05/2021.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

class Task {
private:
    std::string description;
    int duration;
    int priority;
public:
    Task();
    Task(const std::string& description, int duration, int priority);
    Task(const Task& task);

    std::string getDescription() const;
    int getDuration() const;
    int getPriority() const;

    void setDescription(const std::string& newDescription);
    void setDuration(int newDuration);
    void setPriority(int newPriority);

    static std::vector<std::string> tokenize(char delimiter, const std::string& line);
    friend std::istream& operator>>(std::istream& istream, Task& task);
    friend std::ostream& operator<<(std::ostream& ostream, const Task& task);

    bool operator==(const Task& otherTask) const;
    ~Task();

};
