#include <QApplication>
#include <Service.h>
#include <Repository.h>
#include <GUI.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::string prog = "../team.txt";
    std::string sources = "../sources.txt";
    Repository repository{prog, sources};
    Service service{repository};
    std::vector<Programmer> programmers = repository.getAllProgrammers();
    for (auto& programmer: programmers) {
        GUI* window = new GUI{service, programmer};
        window->setWindowTitle(QString::fromStdString(programmer.getName()));
        service.addObserver(window);
        window->show();
    }
    Circles* charts = new Circles{service};
    service.addObserver(charts);
    charts->show();
    return a.exec();
}

