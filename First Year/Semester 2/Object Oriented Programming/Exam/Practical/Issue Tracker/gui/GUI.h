//
// Created by selen on 19/06/2021.
//

#pragma once

#include <QWidget>
#include <Observer.h>
#include <Service.h>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GUI: public QWidget, public Observer {
public:
    GUI(Service& service, User& user);
private:
    Service& service;
    User& user;

    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    void update() override;
    void addIssue();
    void removeIssue();
    void updateIssue();
    void resolveActive();

    int getSelectedIndex() const;

    QListWidget* issuesList;
    QLineEdit* descriptionLineEdit;
    QPushButton* addButton, *removeButton, *resolveButton;
};

