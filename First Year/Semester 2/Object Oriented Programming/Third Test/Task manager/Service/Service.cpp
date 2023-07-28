//
// Created by selen on 21/05/2021.
//

#include "Service.h"

Service::Service(Repository &repository): repository{repository} {
}

std::vector<Task> Service::getAllElements() {
    return this->repository.getAll();
}

int Service::getDurationByPriority(int priority) {
    int duration = 0;
    std::vector<Task> allTasks = this->getAllElements();
    for (auto& task: allTasks) {
        if (task.getPriority() == priority)
            duration += task.getDuration();
    }
    return duration;
}

Service::~Service() = default;
