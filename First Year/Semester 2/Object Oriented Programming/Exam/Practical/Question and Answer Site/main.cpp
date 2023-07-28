#include <QApplication>
#include <string>
#include <Repository.h>
#include <Service.h>
#include <GUI.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::string user = "../users.txt";
    std::string questions = "../questions.txt";
    std::string answers = "../answers.txt";
    Repository repository{user, questions, answers};
    Service service{repository};
    std::vector<User> users = repository.getAllUsers();
    for (auto& use: users) {
        GUI* window = new GUI{service, use};
        window->setWindowTitle(QString::fromStdString(use.getName()));
        service.addObserver(window);
        window->show();
    }
    Search search{service};
    service.addObserver(&search);
    search.show();
    return a.exec();
}

