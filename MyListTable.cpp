#include "MyListTable.h"
#include <QFont>
#include <QBrush>

MyListTableModel::MyListTableModel(Service service, QObject *parent) :
        QAbstractTableModel{parent}, service{service} {}

MyListTableModel::~MyListTableModel() {
}

int MyListTableModel::rowCount(const QModelIndex &parent) const {
    return this->service.getVictimFiles().size();
}

int MyListTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant MyListTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    std::vector<VictimFile> victimFiles = this->service.getMyList();

    if (row == victimFiles.size()) {
        return QVariant{};
    }

    VictimFile file = victimFiles[row];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(file.getName());
            case 1:
                return QString::fromStdString(file.getPlaceOfOrigin());
            case 2:
                return QString::fromStdString(to_string(file.getAge()));
            case 3:
                return QString::fromStdString(file.getPhotography());
            default:
                break;
        }
    }
    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }
    if (role == Qt::BackgroundRole) {
        if (row % 2 == 0) {
            return QBrush{QColor{180, 180, 180}};
        }
    }

    return QVariant{};
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString{"Name"};
                case 1:
                    return QString{"Place of origin"};
                case 2:
                    return QString{"Age"};
                case 3:
                    return QString{"Photography"};
                default:
                    break;
            }
        }
    }
    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}

Qt::ItemFlags MyListTableModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
