//
// Created by selen on 18/06/2021.
//

#include "classes.h"

#include <utility>

void CreateAction::execute() {
    std::cout << "Create file\n";
}

void ExitAction::execute() {
    std::cout << "Exit application\n";
}

MenuItem::MenuItem(Action *action, const std::string& text) {
    this->action = action;
    this->text = text;
}

MenuItem::MenuItem(const std::string& text) {
    this->text = text;
    this->action = nullptr;
}

MenuItem::MenuItem() = default;

void MenuItem::print() {
    std::cout << this->text << "\n";
}

void MenuItem::clicked() {
    this->print();
    if (this->action != nullptr)
        this->action->execute();
}

Menu::Menu(const std::string &text) : MenuItem(text) {
}

Menu::Menu(Action* action, const std::string &text): MenuItem(action, text) {
}


void Menu::add( MenuItem* item) {
    this->items.push_back(item);
}

void Menu::print() {
    MenuItem::print();
    for (auto element: this->items) {
        std::cout<<"\t";
        element->print();
    }
}

void Menu::clicked() {
    if (this->action != nullptr)
        this->action->execute();
    for (auto element: this->items) {
        if (element->action != nullptr)
            element->action->execute();
    }
}

MenuBar::MenuBar() = default;

void MenuBar::add(Menu* menu) {
    this->menus.push_back(menu);
}

void MenuBar::print() {
    for (auto element: this->menus)
        element->print();
}
