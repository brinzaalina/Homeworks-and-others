//
// Created by selen on 18/06/2021.
//

#pragma once
#include <iostream>
#include <vector>

class Action {
public:
    virtual void execute() = 0;
};

class CreateAction: public Action {
public:
    void execute() override;
};

class ExitAction: public Action {
public:
    void execute() override;
};

class MenuItem {
protected:
    std::string text;
public:
    Action* action;
public:
    MenuItem(Action* action, const std::string& text);
    explicit MenuItem(const std::string& text);
    MenuItem();
    virtual void print();
    virtual void clicked();
    ~MenuItem() {
        delete action;
    }
};

class Menu: public MenuItem{
private:
    std::vector<MenuItem*> items;
public:
    explicit Menu(const std::string &text);
    Menu(Action* action, const std::string &text);
    void add(MenuItem* item);
    void print() override;
    void clicked() override;
    ~Menu() {
        for (auto element: items)
            delete element;
    }
};

class MenuBar {
private:
    std::vector<Menu*> menus;
public:
    MenuBar();
    void add(Menu* menu);
    void print();
    ~MenuBar() {
        for (auto element: menus)
            delete element;
    }
};