#include <crtdbg.h>
#include <repository.h>
#include <service.h>
#include <QApplication>
#include <validator.h>
#include "GUI/GUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::vector<Dog> adminRepoVector;
    adminRepoVector.reserve(10);
    std::string filename = R"(D:\GitHub\a89-911-Brinza-Alina-Elena\dogs.txt)";
    Repository repo{adminRepoVector, filename};
    repo.initialiseRepo();
    Service service{repo};
    UserService userService{repo};
    DogValidator validator{};
    GUI gui{service, userService, validator, repo};
    gui.show();
    return a.exec();
}

