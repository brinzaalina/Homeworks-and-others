#pragma once

#include <QWidget>
#include <observer/Observer.h>
#include <Service.h>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QAbstractTableModel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChart>

class SourceTableModel: public QAbstractTableModel {
private:
    Service& service;
public:
    explicit SourceTableModel(Service& newService);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void update();
};

class GUI: public QWidget, public Observer {
public:
    GUI(Service& service, Programmer& programmer);
private:
    Service& service;
    Programmer& programmer;

    void initGUI();
    void createTable();
    void enableSorting();
    void connectSignalsAndSlots();
    void update() override;
    void addSource();
    void updateSource();

    int getSelectedIndex() const;

    SourceTableModel* tableModel;
    QSortFilterProxyModel* proxyModel;
    QTableView* table;
    QLabel* revised, *remained;
    QLineEdit* nameLineEdit;
    QPushButton* addButton, *updateButton;
};

class Circles: public QWidget, public Observer{
private:
    Service& service;
    std::vector<Programmer> programmers;
    std::vector<QtCharts::QChart*> charts;
    QHBoxLayout* layout1;
public:
    Circles(Service& service);
    void createCharts();
    void update() override;
};