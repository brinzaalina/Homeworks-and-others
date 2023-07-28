//
// Created by selen on 18/06/2021.
//
#include "classes.h"

void menu() {
    auto* create = new CreateAction();
    auto* exit = new ExitAction();

    auto New = new Menu{ "New" };
    auto Text = new Menu{ create, "Text" };
    auto Cpp = new Menu{ create, "C++" };
    New->add(Text);
    New->add(Cpp);

    auto File = new Menu{ "File" };
    File->add(New);
    auto Exit = new Menu{ exit, "Exit" };
    File->add(Exit);

    auto About = new Menu{ "About" };

    MenuBar menuBar{};
    menuBar.add(File);
    menuBar.add(About);

    std::cout << "Open menu bar\n";
    menuBar.print();
    std::cout << "\n";

    std::cout << "Clicking File \n";
    File->print();
    std::cout << "\n";

    std::cout << "Clicking New \n";
    New->print();
    std::cout << "\n";

    std::cout << "Clicking C++\n";
    Cpp->clicked();
    std::cout << "\n";

    std::cout << "Clicking Exit\n";
    Exit->clicked();
    std::cout << "\n";
}

int main() {
    menu();
    return 0;
}