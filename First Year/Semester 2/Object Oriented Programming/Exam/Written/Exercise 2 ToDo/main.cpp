//
// Created by selen on 18/06/2021.
//
#include "clases.h"

void ToDoList() {
    ToDo<Activity> todo{};
    Activity tiff{"go to TIFF movie", "20:00"};
    todo += tiff;
    Activity project{"present project assignment", "09:20"};
    todo += project;

    for (auto a: todo)
        std::cout << a << '\n' ;

    todo.reversePrint(std::cout);
}

int main() {
    ToDoList();
    return 0;
}