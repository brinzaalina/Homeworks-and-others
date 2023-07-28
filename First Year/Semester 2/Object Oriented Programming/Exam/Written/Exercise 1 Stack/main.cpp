//
// Created by selen on 17/06/2021.
//
#include <iostream>
#include <cassert>
#include <cstring>
#include "Stack.h"

void testStack() {
    Stack<std::string> s{ 2 };
    assert(s.getMaxCapacity() == 2);
    try {
        s = s + "examination";
        s = s + "oop";
        s = s + "test";
    } catch (std::exception& e) {
        assert(strcmp(e.what(), "Stack is full!") == 0);
    }
    try {
        assert(s.pop() == "oop");
        assert(s.pop() == "examination");
    } catch (std::exception& e) {
        assert(strcmp(e.what(), "Stack is empty!") == 0);
    }
}

int main(){
    testStack();
}