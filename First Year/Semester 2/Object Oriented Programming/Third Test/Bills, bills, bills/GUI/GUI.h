//
// Created by selen on 19/05/2021.
//

#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "Service.h"

class GUI: public QWidget {
public:
    explicit GUI(Service& service);
    ~GUI() override;

private:
    Service& service;
    QListWidget* billListWidget;
    QPushButton* sortButton, *totalButton;
    QLineEdit* companyLineEdit, *unpaidBillsLineEdit;
    void populateList();
    void connectSignalsAndSlots();
    void initGUI();
    void sortList();
    void calculateTotal();
};
