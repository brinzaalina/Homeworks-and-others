#pragma once

#include <QWidget>
#include <observer/Observer.h>
#include <Service.h>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GUI: public QWidget, public Observer {
public:
    explicit GUI(Service& service);
private:
    Service& service;

    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    void update() override;
    void addObject();
    void removeObject();
    void updateObject();

    int getSelectedIndex() const;

//    QListWidget* list;
//    QLineEdit* lineEdit;
//    QPushButton* addButton, *removeButton, *updateButton;
};