//
// Created by selen on 18/06/2021.
//

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

template <typename TElement>
class ToDo: public std::vector<TElement>{
private:
public:
    ToDo& operator+=(const TElement& element);
    void reversePrint(std::ostream& stream);
};

template <typename TElement>
ToDo<TElement>& ToDo<TElement>::operator+=(const TElement &element) {
    this->push_back(element);
    std::sort(this->begin(), this->end());
    return *this;
}

template <typename TElement>
void ToDo<TElement>::reversePrint(std::ostream &stream) {
    for (auto a = this->rbegin(); a != this->rend(); ++a) {
        stream << *a << '\n';
    }
}

class Activity {
private:
    std::string description;
    std::string time;
public:
    Activity(const std::string& description, const std::string& time);
    bool operator<(const Activity& activity) const;

    friend std::ostream& operator<<(std::ostream& ostream, const Activity& activity);
};
