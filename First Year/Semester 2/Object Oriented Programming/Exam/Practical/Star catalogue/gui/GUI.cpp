//
// Created by selen on 21/06/2021.
//

#include <QVBoxLayout>
#include <QHeaderView>
#include <QFormLayout>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <Exceptions.h>
#include <QPainter>
#include "GUI.h"

TableModel::TableModel(Service &newService): service{newService} {

}

int TableModel::rowCount(const QModelIndex &parent) const {
    return this->service.getAllStars().size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    Star currentStar = this->service.getAllStars()[row];
    int column = index.column();
    if (role == Qt::DisplayRole){
        switch (column) {
            case 0:
                return QString::fromStdString(currentStar.getName());
            case 1:
                return QString::fromStdString(currentStar.getConstellation());
            case 2:
                return QString::fromStdString(std::to_string(currentStar.getRA()));
            case 3:
                return QString::fromStdString(std::to_string(currentStar.getDec()));
            case 4:
                return QString::fromStdString(std::to_string(currentStar.getDiameter()));
            default:
                break;
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("Constellation");
                case 2:
                    return QString("RA");
                case 3:
                    return QString("Dec");
                case 4:
                    return QString("Diameter");
                default:
                    break;
            }
        }
    }
    return QVariant();
}

void TableModel::update() {
    QModelIndex topLeft = this->index(1,1);
    QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}


GUI::GUI(Service &service, Astronomer &astronomer): service{service}, astronomer{astronomer} {
    this->createTable();
    this->starList = new QListWidget{};
    this->filterCheck = new QCheckBox{"See only your constellation"};
    this->nameEdit = new QLineEdit{};
    this->RAEdit = new QLineEdit{};
    this->DecEdit = new QLineEdit{};
    this->diameterEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->filterEdit = new QLineEdit{};
    this->viewButton = new QPushButton("View");
    this->initGUI();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto layout = new QVBoxLayout(this);

    auto tableAndListLayout = new QHBoxLayout{};
    tableAndListLayout->addWidget(this->tableView);
    tableAndListLayout->addWidget(this->starList);
    layout->addLayout(tableAndListLayout);

    layout->addWidget(this->filterCheck);

    auto editsLayout = new QFormLayout{};
    editsLayout->addRow("Name:", this->nameEdit);
    editsLayout->addRow("RA:", this->RAEdit);
    editsLayout->addRow("Dec:", this->DecEdit);
    editsLayout->addRow("Diameter:", this->diameterEdit);

    layout->addLayout(editsLayout);

    layout->addWidget(this->addButton);

    auto filterLayout = new QFormLayout{};
    filterLayout->addRow("Filter:", this->filterEdit);
    layout->addLayout(filterLayout);

    layout->addWidget(this->viewButton);
}

void GUI::createTable() {
    this->tableModel = new TableModel{this->service};
    this->tableView = new QTableView{};
    this->tableView->setModel(this->tableModel);
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableView->resizeColumnsToContents();
    this->tableView->resizeRowsToContents();
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->filterEdit, &QLineEdit::textChanged, this, &GUI::filterStars);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addStar);
    QObject::connect(this->filterCheck, &QCheckBox::stateChanged, this, &GUI::showOnlyConstellation);
    QObject::connect(this->viewButton, &QPushButton::clicked, this, &GUI::viewStars);
}

void GUI::update() {
    this->tableModel->update();
}

void GUI::addStar() {
    std::string name = this->nameEdit->text().toStdString();
    if (name.empty()) {
        QMessageBox::critical(this, "Error", "Invalid name!");
        return;
    }
    int RA;
    std::string RAstring = this->RAEdit->text().toStdString();
    if (RAstring.empty())
        RA = 0;
    else
        RA = std::stoi(RAstring);
    int Dec;
    std::string DecString = this->DecEdit->text().toStdString();
    if (DecString.empty())
        Dec = 0;
    else
        Dec = std::stoi(DecString);
    int diameter;
    std::string diameterString = this->diameterEdit->text().toStdString();
    if (diameterString.empty())
        diameter = 0;
    else
        diameter = std::stoi(diameterString);
    if (diameter <= 0) {
        QMessageBox::critical(this, "Error", "Invalid diameter!");
        return;
    }
    try {
        this->service.addStar(name, this->astronomer.getConstellation(), RA, Dec, diameter);
    } catch (RepositoryException& ex) {
        QMessageBox::critical(this, "Error", ex.what());
        return;
    }
}

void GUI::showOnlyConstellation() {
    if (this->filterCheck->isChecked()) {
        QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
        proxyModel->setSourceModel(this->tableModel);
        this->tableView->setSortingEnabled(true);
        proxyModel->setFilterRegExp(QRegExp(QString::fromStdString(this->astronomer.getConstellation()), Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterKeyColumn(1);

        this->tableView->setModel(proxyModel);
        this->tableView->resizeRowsToContents();
    } else {
        this->tableView->setModel(this->tableModel);
        this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->tableView->resizeRowsToContents();
        this->tableView->resizeColumnsToContents();
    }
}

void GUI::filterStars() {
    this->starList->clear();
    std::string stringFilter = this->filterEdit->text().toStdString();
    std::vector<Star> stars = this->service.getFiltered(stringFilter);
    for (auto& star: stars){
        this->starList->addItem(QString::fromStdString(star.getName() + " - " + star.getConstellation() + " - " + std::to_string(star.getRA()) + " - " + std::to_string(star.getDec()) + " - " + std::to_string(star.getDiameter())));
    }
}

void GUI::viewStars() {
    ViewStars* viewConstellation = new ViewStars{this->service, this->astronomer.getConstellation()};
    viewConstellation->show();
}

ViewStars::ViewStars(Service &service, std::string constellation): service{service}, constellation(constellation) {
    this->paint();
}

void ViewStars::update() {
    this->paint();
}

void ViewStars::paint() {
    QPainter painter{ this };
    painter.eraseRect(0, 0, 600, 400);
    std::vector<Star> allStars = this->service.getAllStars();
    for (auto star: allStars) {
        if (star.getConstellation() == constellation) {
            QPen pen{ Qt::black, 1, Qt::SolidLine, Qt::RoundCap };
            painter.setPen(pen);
            painter.drawEllipse(star.getRA(), star.getDec(), star.getDiameter(), star.getDiameter());
        }
    }
}

QSize ViewStars::sizeHint() const {
    return QSize{ 600, 400 };
}

void ViewStars::paintEvent(QPaintEvent *event) {
    this->paint();
}
