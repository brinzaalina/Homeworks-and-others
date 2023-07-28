#pragma once

#include <QWidget>
#include <Service.h>
#include <QAbstractTableModel>
#include <QTableView>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include "Observer.h"

class TableModel: public QAbstractTableModel {
private:
    Service& service;
public:
    explicit TableModel(Service& newService);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void update();
};

class GUI: public QWidget, public Observer {
private:
    Service& service;
    Astronomer& astronomer;
    TableModel* tableModel;
    QTableView* tableView;
    QLineEdit* nameEdit, *RAEdit, *DecEdit, *diameterEdit;
    QLineEdit* filterEdit;
    QListWidget* starList;
    QPushButton* addButton, *viewButton;
    QCheckBox* filterCheck;
public:
    GUI(Service& service, Astronomer& astronomer);

private:
    void initGUI();
    void createTable();
    void connectSignalsAndSlots();
    void update() override;
    void addStar();
    void showOnlyConstellation();
    void filterStars();
    void viewStars();
};

class ViewStars: public QWidget, public Observer {
private:
    Service& service;
    std::string constellation;
    void paint();
    void update() override;

public:
    ViewStars(Service& service, std::string constellation);
    QSize sizeHint() const override;
    ~ViewStars() = default;

protected:
    void paintEvent(QPaintEvent* event) override;
};