#include "GUI.h"
#include <QtWidgets/QApplication>
#include <memory>
#include "Repository.h"
#include "Service.h"
#include "Domain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string path{ R"(D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Third Test\Bills, bills, bills\input.txt)" };
    std::vector<Bill> repoVector;
    std::unique_ptr<Repository> repository = std::make_unique<Repository>(repoVector, path);
    Service service{*repository};
    GUI app{service};
    app.show();
    return a.exec();
}