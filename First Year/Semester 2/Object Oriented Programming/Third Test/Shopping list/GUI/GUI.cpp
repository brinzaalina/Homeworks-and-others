//
// Created by selen on 21/05/2021.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "GUI.h"
GUI::GUI(Service &service): service{service} {
    this->productsListWidget = new QListWidget{this};
    this->deleteNameLineEdit = new QLineEdit{};
    this->categoryFilterLineEdit = new QLineEdit{};
    this->deletePushButton = new QPushButton{"Delete"};
    this->filterPushButton = new QPushButton{"Filter"};
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout{this};
    layout->addWidget(this->productsListWidget);

    auto* deleteLayout = new QFormLayout{this};
    deleteLayout->addRow("Name:", this->deleteNameLineEdit);
    deleteLayout->addRow(this->deletePushButton);
    layout->addLayout(deleteLayout);

    auto* filterLayout = new QFormLayout{this};
    filterLayout->addRow("Category:", this->categoryFilterLineEdit);
    filterLayout->addRow(this->filterPushButton);
    layout->addLayout(filterLayout);
}

void GUI::populateList() {
    this->productsListWidget->clear();
    std::vector<Product> allProducts = this->service.getAllElements();
    for (auto& product: allProducts) {
        this->productsListWidget->addItem(QString::fromStdString(
                product.getCategory() + " | " + product.getName() + " | " + std::to_string(product.getQuantity())));
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->deletePushButton, &QPushButton::clicked, this, &GUI::deleteProduct);
    QObject::connect(this->filterPushButton, &QPushButton::clicked, this, &GUI::filterProducts);
}

void GUI::deleteProduct() {
    try {
        std::string name = this->deleteNameLineEdit->text().toStdString();
        this->service.remove(name);
        this->populateList();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting product!");
        error->exec();
    }
}

void GUI::filterProducts() {
    std::string category = this->categoryFilterLineEdit->text().toStdString();
    if (category.empty())
        populateList();
    else {
        auto validProducts = this->service.getAllFromCategory(category);
        this->productsListWidget->clear();
        for (Product& product: validProducts)
            this->productsListWidget->addItem(QString::fromStdString(product.getCategory() + " | " + product.getName() + " | " + std::to_string(product.getQuantity())));
    }
}


GUI::~GUI() = default;
