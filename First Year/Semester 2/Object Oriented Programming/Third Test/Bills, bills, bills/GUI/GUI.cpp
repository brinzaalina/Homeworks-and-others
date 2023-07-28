//
// Created by selen on 19/05/2021.
//

#include <QVBoxLayout>
#include <QLabel>
#include "GUI.h"

GUI::GUI(Service &service): service{service} {
    this->billListWidget = new QListWidget{this};
    this->sortButton = new QPushButton{"Sort"};
    this->totalButton = new QPushButton{"Calculate total"};
    this->companyLineEdit = new QLineEdit{};
    this->unpaidBillsLineEdit = new QLineEdit{};
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto * layout = new QVBoxLayout(this);
    layout->addWidget(this->billListWidget);

    layout->addWidget(this->sortButton);

    auto* unpaidBillsLayout = new QGridLayout{};
    this->companyLineEdit->setPlaceholderText("Company name");
    auto* labelCompanyLineEdit = new QLabel{"Company name: "};
    labelCompanyLineEdit->setBuddy(this->companyLineEdit);
    unpaidBillsLayout->addWidget(labelCompanyLineEdit);
    unpaidBillsLayout->addWidget(this->companyLineEdit);
    auto* labelUnpaidLineEdit = new QLabel{"Total: "};
    labelUnpaidLineEdit->setBuddy(this->unpaidBillsLineEdit);
    unpaidBillsLayout->addWidget(labelUnpaidLineEdit);
    unpaidBillsLayout->addWidget(this->unpaidBillsLineEdit);
    unpaidBillsLayout->addWidget(this->totalButton);

    layout->addLayout(unpaidBillsLayout);
}

void GUI::populateList() {
    this->billListWidget->clear();
    std::vector<Bill> allBills = this->service.getAllElements();
    for (auto& bill: allBills) {
        this->billListWidget->addItem(QString::fromStdString(bill.getCompanyName()+", "+std::to_string(bill.getSum())));
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->sortButton, &QPushButton::clicked, this, &GUI::sortList);
    QObject::connect(this->totalButton, &QPushButton::clicked, this, &GUI::calculateTotal);
}

void GUI::sortList() {
    this->billListWidget->setSortingEnabled(true);
    this->populateList();
}

void GUI::calculateTotal() {
    std::string companyName = this->companyLineEdit->text().toStdString();
    float total = this->service.getUnpaidBillsTotal(companyName);
    this->unpaidBillsLineEdit->clear();
    this->unpaidBillsLineEdit->setText(QString::fromStdString(std::to_string(total)));
}

GUI::~GUI() = default;
