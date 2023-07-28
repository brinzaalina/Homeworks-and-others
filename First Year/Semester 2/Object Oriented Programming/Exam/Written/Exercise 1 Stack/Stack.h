//
// Created by selen on 17/06/2021.
//
#include <vector>
#include <iostream>

#pragma once

class myException: public std::exception {
private:
    std::string message;
public:
    explicit myException(std::string& _message): message(_message) {
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

template <typename TElement>
class Stack {
private:
    std::vector<TElement> elements;
    int maxCapacity;
public:
    explicit Stack(int maxCapacity);
    int getMaxCapacity();
    const TElement pop();
    ~Stack() = default;

    Stack<TElement> operator+(const TElement& element);
};

template <typename TElement>
Stack<TElement>::Stack(int maxCapacity): maxCapacity{maxCapacity} {
}

template <typename TElement>
int Stack<TElement>::getMaxCapacity() {
    return maxCapacity;
}

template <typename TElement>
const TElement Stack<TElement>::pop() {
    if (elements.empty()) {
        std::string message;
        message.append("Stack is empty!");
        throw myException(message);
    }
    const TElement element = elements[elements.size() - 1];
    elements.pop_back();
    return element;
}

template <typename TElement>
Stack<TElement> Stack<TElement>::operator+(const TElement& element) {
    Stack<TElement> temp{ maxCapacity };
    if (elements.size() == 2) {
        std::string message;
        message.append("Stack is full!");
        throw myException(message);
    }
    temp.elements = elements;
    temp.elements.push_back(element);
    return temp;
}




