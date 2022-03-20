//
// Created by selen on 04/05/2021.
//

#ifndef A89_911_BRINZA_ALINA_ELENA_GUI_H
#define A89_911_BRINZA_ALINA_ELENA_GUI_H

#include <QWidget>
#include <service.h>
#include <QLabel>
#include <QPushButton>
#include <userservice.h>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <validator.h>
class DogListModel: public QAbstractListModel {
private:
    Repository& repository;
public:
    explicit DogListModel(Repository& repo): repository{ repo } {};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

class GUI: public QWidget {
private:
    Service& service;
    UserService& userService;
    DogValidator& validator;
    Repository& repository;
    void initGUI();
    QLabel* titleWidget;
    QPushButton* adminButton;
    QPushButton* userButton;
    void showAdmin();
    void showUser();
    void connectSignalsAndSlots();
public:
    explicit GUI(Service& serv, UserService& userserv, DogValidator& validator1, Repository& repository;);
    ~GUI() override;
};

class AdminGUI: public QWidget {
private:
    Service& service;
    DogValidator& validator;
    Repository& repository;
    void initAdminGUI();
    QLabel* titleWidget;
    QListWidget* dogsListWidget;
    QLineEdit* nameLineEdit, *breedLineEdit, *ageLineEdit, *linkLineEdit;
    QPushButton* addButton, *deleteButton, *updateButton, *chartButton;
    DogListModel* listModel;

    void populateList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addDog();
    void deleteDog();
    void updateDog();
    void displayChart();

    QWidget* chartWindow;
public:
    explicit AdminGUI(QWidget* parent, Service& serv, DogValidator& validator1, Repository& repo);
    ~AdminGUI() override;
};

class UserGUI: public QWidget {
private:
    Service& service;
    UserService& userService;
    DogValidator& validator;
    void initUserGUI();
    QLabel* titleWidget;
    QListWidget* dogsListWidget, *adoptionListWidget;
    QLineEdit* nameLineEdit, *breedLineEdit, *ageLineEdit, *linkLineEdit, *breedFilterLineEdit, *ageFilterLineEdit;
    QPushButton* addButton, *filterButton, *openListButton;
    QRadioButton* csvButton, *htmlButton;
    bool repoTypeSelected;
    bool filtered;
    void populateDogList();
    void populateAdoptionList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addDog();
    void filterDogs();
public:
    explicit UserGUI(QWidget* parent, Service& serv, UserService& userserv, DogValidator& validator1);
    ~UserGUI() override;
};


#endif //A89_911_BRINZA_ALINA_ELENA_GUI_H
