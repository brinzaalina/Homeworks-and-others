//
// Created by selen on 21/05/2021.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include "GUI.h"
GUI::GUI(Service &service): service{service} {
    this->familyListWidget = new QListWidget{this};
    this->vegetablesListWidget = new QListWidget{this};
    this->searchButton = new QPushButton{"Search"};
    this->vegetableLineEdit = new QLineEdit{};
    this->consumedLineEdit = new QLineEdit{};
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout(this);
    auto* listsLayout = new QHBoxLayout(this);
    listsLayout->addWidget(this->familyListWidget);
    listsLayout->addWidget(this->vegetablesListWidget);
    layout->addLayout(listsLayout);

    auto* consumedLayout = new QFormLayout(this);
    consumedLayout->addRow("Name:", this->vegetableLineEdit);
    consumedLayout->addRow("Consumable parts:", this->consumedLineEdit);
    layout->addLayout(consumedLayout);

    layout->addWidget(this->searchButton);
}

void GUI::populateList() {
    this->familyListWidget->clear();
    this->familyListWidget->setSortingEnabled(true);
    std::vector<Vegetable> allVegetables = this->service.getAllElements();
    for (auto& vegetable: allVegetables) {
        if (std::find(allFamilies.begin(), allFamilies.end(), vegetable.getFamily()) == allFamilies.end())
            allFamilies.push_back(vegetable.getFamily());
    }
    for (auto& family: allFamilies) {
        this->familyListWidget->addItem(QString::fromStdString(family));
    }
    this->familyListWidget->sortItems();
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->familyListWidget, &QListWidget::itemSelectionChanged, this, &GUI::vegetableList);
    QObject::connect(this->searchButton, &QPushButton::clicked, this, &GUI::getVegetable);
}

std::string GUI::getSelectedItem() const {
    return this->familyListWidget->currentItem()->text().toStdString();
}

void GUI::vegetableList() {
    this->vegetablesListWidget->clear();
    std::string family = this->getSelectedItem();
    std::vector<std::string> vegetables = this->service.vegetableList(family);
    for (auto& vegetable: vegetables) {
        this->vegetablesListWidget->addItem(QString::fromStdString(vegetable));
    }
}

void GUI::getVegetable() {
    std::string name = this->vegetableLineEdit->text().toStdString();
    std::string consumables = this->service.getConsumables(name);
    this->consumedLineEdit->setText(QString::fromStdString(consumables));

    QString family = QString::fromStdString(this->service.getFamilyByName(name));
    for (int i = 0; i < this->familyListWidget->count(); ++i) {
        auto* item = this->familyListWidget->item(i);
        if (item->text() == family) {
            this->familyListWidget->item(i)->setSelected(true);
            this->familyListWidget->setFocus();
            this->vegetablesListWidget->clear();
        }
    }
}

GUI::~GUI() = default;
