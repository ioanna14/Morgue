#ifndef MORGUE_GUI_H
#define MORGUE_GUI_H

#include "Domain.h"
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QTableView>
#include "Service.h"
#include "MyListTable.h"

class GUI: public QWidget
{
    Q_OBJECT
public:
    GUI(Service service, QWidget *parent = 0);
    ~GUI();

private:
    Service service;
    QWidget* modeA;
    QPushButton* modeAButton;
    QPushButton* goBackModeA;
    QListWidget* victimFilesList;
    QLineEdit* nameEdit;
    QLineEdit* placeOfOriginEdit;
    QLineEdit* ageEdit;
    QLineEdit* photographyEdit;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QShortcut* shortcutUndo;
    QShortcut* shortcutRedo;

    QWidget* modeB;
    QPushButton* modeBButton;
    QPushButton* goBackModeB;
    QListWidget* myList;
    QLineEdit* filterAgeEdit;
    QLineEdit* filterPlaceOfOriginEdit;
    QPushButton* filterButton;
    QPushButton* nextButton;
    QPushButton* saveButton;
    QPushButton* mylistButton;
    QPushButton* mylistWindowButton;
    QLineEdit* nextEdit;
    QLineEdit* saveEdit;
    MyListTableModel* myListTableModel;
    QTableView* mylistTableView;


    void initGUI();
    int getSelectedIndex();
    void connectSignalsAndSlots();

    void populateVictimFilesList();
    void listItemChanged();

    void goBackButtonHandler();
    void modeAButtonHandler();
    void modeBButtonHandler();

    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();

    void filterButtonHandler();
    void nextButtonHandler();
    void saveButtonHandler();
    void mylistButtonHandler();
    void mylistWindowButtonHandler();

    void filterAge();
    void filterPlaceOfOrigin();
    void filterAgeAndPlaceOfOrigin();

    void undoButtonHandler();
    void redoButtonHandler();

signals:
    void updatedSignal();

};

#endif
