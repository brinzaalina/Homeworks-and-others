//
// Created by selen on 19/06/2021.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "GUI.h"

GUI::GUI(Service &service, User& user): service{service},user{user} {
    this->issuesList = new QListWidget{};
    this->descriptionLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->removeButton = new QPushButton("Remove");
    this->resolveButton = new QPushButton("Resolve");
    if (user.getType() == "tester")
        this->resolveButton->setEnabled(false);
    if (user.getType() == "programmer")
        this->addButton->setEnabled(false);
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(this->issuesList);

    auto lineEditLayout = new QFormLayout{};
    lineEditLayout->addRow("Description:", this->descriptionLineEdit);
    layout->addLayout(lineEditLayout);

    auto buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->removeButton, 0, 1);
    buttonsLayout->addWidget(this->resolveButton, 0, 2);
    layout->addLayout(buttonsLayout);
}

void GUI::populateList() {
    this->issuesList->clear();
    std::vector<Issue> allIssues = this->service.getAllIssues();
    for (Issue& issue: allIssues)
        this->issuesList->addItem(QString::fromStdString(issue.getDescription() + "," + issue.getStatus() + "," + issue.getReporter() + "," + issue.getSolver()));
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addIssue);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeIssue);
    QObject::connect(this->resolveButton, &QPushButton::clicked, this, &GUI::updateIssue);
    QObject::connect(this->issuesList, &QListWidget::itemSelectionChanged, this, &GUI::resolveActive);
}

void GUI::update() {
    this->populateList();
}

void GUI::addIssue() {
    std::string description = this->descriptionLineEdit->text().toStdString();
    try {
        this->service.addIssue(description, this->user.getName());
    } catch (std::exception& ex) {
        auto error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ex.what());
        error->setWindowTitle("Error!");
        error->exec();
    }
}

void GUI::removeIssue() {
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex == -1) {
        auto error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText("No issue selected!");
        error->setWindowTitle("Error!");
        error->exec();
    } else {
        try {
            this->service.removeIssue(this->service.getAllIssues()[selectedIndex].getDescription());
        } catch (std::exception& ex) {
            auto error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(ex.what());
            error->setWindowTitle("Error!");
            error->exec();
        }
    }
}

void GUI::updateIssue() {
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex == -1) {
        auto error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText("No issue selected!");
        error->setWindowTitle("Error!");
        error->exec();
    } else {
        try {
            this->service.updateIssue(this->service.getAllIssues()[selectedIndex].getDescription(), this->user.getName());
        } catch (std::exception& ex) {
            auto error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(ex.what());
            error->setWindowTitle("Error!");
            error->exec();
        }
    }
}

void GUI::resolveActive() {
    if (this->user.getType() == "programmer") {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex != -1) {
            if (this->service.getAllIssues()[selectedIndex].getStatus() == "open") {
                this->resolveButton->setEnabled(true);
            } else {
                this->resolveButton->setEnabled(false);
            }
        }
    }
}

int GUI::getSelectedIndex() const {
    QModelIndexList selectedIndex = this->issuesList->selectionModel()->selectedIndexes();
    if (selectedIndex.empty()){
        return -1;
    }
    int selected = selectedIndex.at(0).row();
    return selected;
}
