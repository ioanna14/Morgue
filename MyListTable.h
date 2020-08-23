#ifndef MORGUE_MYLISTTABLE_H
#define MORGUE_MYLISTTABLE_H

#include <QAbstractTableModel>
#include "Service.h"

class MyListTableModel : public QAbstractTableModel {
private:
    Service service;

public:
    explicit MyListTableModel(Service service, QObject *parent = nullptr);

    ~MyListTableModel();

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    // Value at a given position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // add header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // used to set certain properties of a cell
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};


#endif //MORGUE_MYLISTTABLE_H
