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
#include <QGridLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <validator.h>
#include <QTableView>
#include <QShortcut>
#include <QHeaderView>

class DogTableModel: public QAbstractTableModel {
private:
    UserRepository* repository;
public:
        explicit DogTableModel(UserRepository *newRepository);

        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        void update();
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
    explicit GUI(Service& serv, UserService& userserv, DogValidator& validator1, Repository& repository);
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
    QPushButton* undoButton, *redoButton;
    QShortcut* shortcutUndo, *shortcutRedo;
    void populateList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addDog();
    void deleteDog();
    void updateDog();
    void displayChart();
    void undoGUI();
    void redoGUI();

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
    QPushButton* undoButton, *redoButton;
    QShortcut* shortcutUndo, *shortcutRedo;
    QRadioButton* csvButton, *htmlButton;
    QTableView* adoptionListTable;
    DogTableModel* adoptionListTableModel;
    QGridLayout* listAndTableLayout;
    bool repoTypeSelected;
    bool filtered;
    void createTable();
    void populateDogList();
    void populateAdoptionList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addDog();
    void filterDogs();
    void undoGUI();
    void redoGUI();
public:
    explicit UserGUI(QWidget* parent, Service& serv, UserService& userserv, DogValidator& validator1);
    ~UserGUI() override;
};


#endif //A89_911_BRINZA_ALINA_ELENA_GUI_H
