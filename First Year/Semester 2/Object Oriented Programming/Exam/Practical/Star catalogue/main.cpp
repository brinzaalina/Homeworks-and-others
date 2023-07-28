#include <QApplication>
#include <Service.h>
#include <Repository.h>
#include <GUI.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::string astro = "../astronomers.txt";
    std::string star = "../stars.txt";
    Repository repository{astro, star};
    Service service{repository};
    std::vector<Astronomer> allAstronomers = repository.getAllAstronomers();
    for (auto& astronomer: allAstronomers) {
        GUI* window = new GUI{service, astronomer};
        window->setWindowTitle(QString::fromStdString(astronomer.getName()));
        service.addObserver(window);
        window->show();
    }
    return a.exec();
}

