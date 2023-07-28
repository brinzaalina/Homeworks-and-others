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
    QListWidget* tasksListWidget;
    QLineEdit* priorityLineEdit, *durationLineEdit;
    QPushButton* showDurationButton;
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    void getDurationByPriority();
public:
    explicit GUI(Service& service);
    ~GUI() override;
};
