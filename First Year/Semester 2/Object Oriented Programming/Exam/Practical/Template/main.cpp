//#include <QApplication>
//#include <GUI.h>
//
//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    std::string file;
//    Repository repository{};
//    Service service{repository};
//    for (auto& user: service.getAllObjects()) {
//        GUI* window = new GUI{service};
//        window->setWindowTitle(QString::fromStdString(std::to_string(user.getElement())));
//        service.addObserver(window);
//        window->show();
//    }
//    return a.exec();
//}
#include <iostream>
using namespace std;
int main()
{
    int A,B;
    char C;
    cin>>A>>B>>C;
    if (C=='+') cout<<A+B;
    if (C=='*') cout<<A*B;
    if (C=='-')
    {
        if (A>B) cout<<A-B;
        else cout<<B-A;
    }
    if (C=='/')
    {
        if (A>B) cout<<A/B;
        else cout<<B/A;
    }
    return 0;
}


