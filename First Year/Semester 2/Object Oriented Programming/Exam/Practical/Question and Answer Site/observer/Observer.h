#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        this->observers.push_back(observer);
    };

    void deleteObserver(Observer* observer) {
        auto iterator = std::find(this->observers.begin(), this->observers.end(), observer);
        if (iterator != observers.end())
            this->observers.erase(iterator);
    }

    void notify() {
        for (auto observer: this->observers)
            observer->update();
    }
};
