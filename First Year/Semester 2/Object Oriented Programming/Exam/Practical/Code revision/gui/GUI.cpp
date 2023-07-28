
#include <QMessageBox>
#include "GUI.h"

SourceTableModel::SourceTableModel(Service& newService): service{newService}{
}

int SourceTableModel::rowCount(const QModelIndex &parent) const {
    return this->service.getAllSources().size();
}

int SourceTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant SourceTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    SourceFile currentFile = this->service.getAllSources()[row];
    int column = index.column();
    if (role == Qt::DisplayRole){
        switch (column) {
            case 0:
                return QString::fromStdString(currentFile.getName());
            case 1:
                return QString::fromStdString(currentFile.getStatus());
            case 2:
                return QString::fromStdString(currentFile.getCreator());
            case 3:
                return QString::fromStdString(currentFile.getReviser());
            default:
                break;
        }
    }
    if (role == Qt::FontRole) {
        if (currentFile.getStatus() == "not revised") {
            QFont font{};
            font.setBold(true);
            return font;
        }
    }
    if (role == Qt::BackgroundColorRole) {
        if (currentFile.getStatus() == "revised") {
            QColor color{};
            color.setNamedColor("Green");
            return color;
        }
    }
    return QVariant();
}

QVariant SourceTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("Status");
                case 2:
                    return QString("Creator");
                case 3:
                    return QString("Reviser");
                default:
                    break;
            }
        }
    }
    return QVariant();
}

void SourceTableModel::update() {
    QModelIndex topLeft = this->index(1,1);
    QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

GUI::GUI(Service &service, Programmer& programmer): service{service}, programmer{programmer} {
    this->createTable();
    this->nameLineEdit = new QLineEdit{};
    this->revised = new QLabel(QString::fromStdString("Revised: " + std::to_string(this->programmer.getRevisedFiles())));
    this->remained = new QLabel(QString::fromStdString("Remained:" + std::to_string(this->programmer.getTotal() - this->programmer.getRevisedFiles())));
    this->addButton = new QPushButton("Add");
    this->updateButton = new QPushButton("Revise");
    this->initGUI();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(this->table);

    auto labels = new QGridLayout();
    labels->addWidget(this->revised, 0, 0);
    labels->addWidget(this->remained, 0 , 1);
    layout->addLayout(labels);

    auto edit = new QFormLayout();
    edit->addRow("Name: ", this->nameLineEdit);
    layout->addLayout(edit);

    auto buttons = new QGridLayout();
    buttons->addWidget(this->addButton, 0, 0);
    buttons->addWidget(this->updateButton, 0, 1);
    layout->addLayout(buttons);
}

void GUI::createTable() {
    this->tableModel = new SourceTableModel{this->service};
    this->table = new QTableView{};
    this->table->setModel(this->tableModel);
    this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->enableSorting();
}

void GUI::enableSorting() {
    this->proxyModel = new QSortFilterProxyModel{};
    this->proxyModel->setSourceModel(this->tableModel);
    this->table->setSortingEnabled(true);
    this->table->setModel(this->proxyModel);
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->table, &QTableView::clicked, [this]() {
        QModelIndexList selectedIndexes = table->selectionModel()->selectedIndexes();
        if (selectedIndexes.at(1).data().toString() == "revised" || selectedIndexes.at(2).data().toString().toStdString() == programmer.getName()) {
            this->updateButton->setDisabled(true);
        } else {
            this->updateButton->setDisabled(false);
        }
    });
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addSource);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateSource);
}

void GUI::update() {
    this->proxyModel->setSourceModel(nullptr);
    this->proxyModel->setSourceModel(this->tableModel);
}

void GUI::addSource() {
    std::string name = this->nameLineEdit->text().toStdString();
    try {
        this->service.addFile(name, this->programmer.getName());
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

void GUI::updateSource() {
    int row = this->getSelectedIndex();
    std::string name = this->table->model()->index(row, 0).data().toString().toStdString();
    try {
        this->service.updateSource(name, this->programmer.getName());
        this->programmer.setRevisedFiles(1);
        this->revised->setText(QString::fromStdString("Revised: " + std::to_string(this->programmer.getRevisedFiles())));
        this->remained->setText(QString::fromStdString("Remained:" + std::to_string(this->programmer.getTotal() - this->programmer.getRevisedFiles())));
        if (this->programmer.getRevisedFiles() == this->programmer.getTotal())
            QMessageBox::information(this, "Congratulations!", "You completed your duties!");
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

int GUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->table->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return -1;
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

Circles::Circles(Service& service): service{service} {
    this->programmers = this->service.getAllProgrammers();
    this->layout1 = new QHBoxLayout(this);
    this->createCharts();
    this->resize(840, 720);
}

void Circles::createCharts() {
    for (auto& programmer: this->programmers) {
        auto *series = new QtCharts::QPieSeries();
        series->append("Revised",programmer.getRevisedFiles());
        series->append("Not revised", programmer.getTotal() - programmer.getRevisedFiles());

        auto * slice = series->slices().at(0);
        slice->setLabelVisible();

        auto* chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle(QString::fromStdString(programmer.getName()));
        chart->legend()->hide();

        this->charts.push_back(chart);
        auto * chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        this->layout1->addWidget(chartView);
    }
}

void Circles::update() {
    this->programmers = this->service.getAllProgrammers();
    for (auto & programmer: this->programmers) {
        for (auto chart: this->charts) {
            if (programmer.getName() == chart->title().toStdString()) {
                auto *series = new QtCharts::QPieSeries();
                series->append("Revised",programmer.getRevisedFiles());
                series->append("Not revised", programmer.getTotal() - programmer.getRevisedFiles());

                auto * slice = series->slices().at(0);
                slice->setLabelVisible();

                chart->addSeries(series);
                chart->legend()->hide();
            }
        }
    }
}
