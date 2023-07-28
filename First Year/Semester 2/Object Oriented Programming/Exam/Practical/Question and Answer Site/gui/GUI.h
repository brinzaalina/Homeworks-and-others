#pragma once

#include <QWidget>
#include <Service.h>
#include <QListWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTreeWidget>
#include "../observer/Observer.h"

class GUI: public QWidget, public Observer {
public:
    GUI(Service& service, User& user);
private:
    Service& service;
    User& user;

    void initGUI();
    void populateList();
    void populateAnswerList();
    void spinBox();
    void connectSignalsAndSlots();
    void update() override;
    void addQuestion();
    void addAnswer();
    void changeVotes();

    int getSelectedIndex() const;
    int getSelectedIndexAnswers() const;

    QListWidget* questionsListWidget, *answersListWidget;
    QSpinBox* votesSpinBox;
    QLineEdit* lineEdit;
    QPushButton* addQuestionButton, *addAnswerPushButton;
    QVBoxLayout* allLayout;
};

class Search: public QWidget, public Observer {
private:
    Service& service;
    QLineEdit* lineEdit;
    QTreeWidget* matchingTreeWidget;

    void connectSignalsAndSlots();
    void filterList();
    void update() override;

public:
    explicit Search(Service& service);
};