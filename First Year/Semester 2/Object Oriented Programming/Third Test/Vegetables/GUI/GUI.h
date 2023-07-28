//
// Created by selen on 21/05/2021.
//

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <Service.h>

#pragma once
class GUI: public QWidget {
private:
    Service& service;
    QListWidget* familyListWidget, *vegetablesListWidget;
    QPushButton* searchButton;
    QLineEdit* vegetableLineEdit, *consumedLineEdit;
    std::vector<std::string> allFamilies;
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    std::string getSelectedItem() const;
    void vegetableList();
    void getVegetable();
public:
    explicit GUI(Service& service);
    ~GUI() override;
};
