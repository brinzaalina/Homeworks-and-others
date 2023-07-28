//
// Created by selen on 21/05/2021.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include "GUI.h"
GUI::GUI(Service &service): service{service} {
    this->tasksListWidget = new QListWidget{this};
    this->priorityLineEdit = new QLineEdit{};
    this->durationLineEdit = new QLineEdit{};
    this->showDurationButton = new QPushButton{"Show duration"};
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(this->tasksListWidget);

    auto* durationLayout = new QFormLayout(this);
    durationLayout->addRow("Priority:", this->priorityLineEdit);
    durationLayout->addRow("Duration:", this->durationLineEdit);
    layout->addLayout(durationLayout);

    layout->addWidget(this->showDurationButton);
}

void GUI::populateList() {
    this->tasksListWidget->clear();
    this->tasksListWidget->setSortingEnabled(true);
    std::vector<Task> allTasks = this->service.getAllElements();
    for (auto& task: allTasks) {
        if (task.getPriority() == 1) {
            auto* newItem = new QListWidgetItem();
            QFont font;
            font.setWeight(75);
            QString itemText = QString::fromStdString(std::to_string(task.getPriority()) + "|" + task.getDescription());
            newItem->setText(itemText);
            newItem->setFont(font);
            this->tasksListWidget->addItem(newItem);
        } else {
            this->tasksListWidget->addItem(QString::fromStdString(std::to_string(task.getPriority()) + "|" + task.getDescription()));
        }
    }
    this->tasksListWidget->sortItems();
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->showDurationButton, &QPushButton::clicked, this, &GUI::getDurationByPriority);
}

void GUI::getDurationByPriority() {
    int priority = stoi(this->priorityLineEdit->text().toStdString());
    int duration = this->service.getDurationByPriority(priority);
    this->durationLineEdit->setText(QString::fromStdString(std::to_string(duration)));
}

GUI::~GUI() = default;
