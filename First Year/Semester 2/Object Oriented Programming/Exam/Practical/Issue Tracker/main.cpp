//
// Created by selen on 19/06/2021.
//
#include <Repository.h>
#include <Service.h>
#include <QApplication>
#include <GUI.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::string users = "../users.txt";
    std::string issues = "../issues.txt";
    Repository repository{users, issues};
    Service service{repository};
    for (auto& user: service.getAllUsers()) {
        GUI* window = new GUI{service, user};
        window->setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));
        service.addObserver(window);
        window->show();
    }
    return a.exec();
}