//
// Created by selen on 21/05/2021.
//
#include <QtWidgets/QApplication>
#include <memory>
#include <GUI.h>

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    std::string filename{R"(D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Third Test\Vegetables\input.txt)"};
    std::vector<Vegetable> repoVector;
    Repository repo{filename, repoVector};
    Service service{repo};
    GUI gui{service};
    gui.show();
    return QApplication::exec();
}
