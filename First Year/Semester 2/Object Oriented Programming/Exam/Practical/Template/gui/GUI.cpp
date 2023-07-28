#include "GUI.h"

GUI::GUI(Service &service): service{service} {
//    this->list = new QListWidget{};
//    this->lineEdit = new QLineEdit{};
//    this->addButton = new QPushButton("Add");
//    this->removeButton = new QPushButton("Remove");
//    this->updateButton = new QPushButton("Update");
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {

}

void GUI::populateList() {

}

void GUI::connectSignalsAndSlots() {
//    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addObject);
//    QObject::connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeObject);
//    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateObject);
}

void GUI::update() {
//    this->populateList();
}

void GUI::addObject() {

}

void GUI::removeObject() {

}

void GUI::updateObject() {

}

int GUI::getSelectedIndex() const {
    return 0;
}
