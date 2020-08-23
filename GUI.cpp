#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QtCore/QSortFilterProxyModel>
#include "Domain.h"
#include "GUI.h"

GUI::GUI(Service controller, QWidget *parent) : QWidget{parent}, service{controller} {
    this->initGUI();
    this->connectSignalsAndSlots();
    this->populateVictimFilesList();
}

GUI::~GUI() {}

void GUI::initGUI() {
    //General layout of the window
    QVBoxLayout *generalLayout = new QVBoxLayout{this};

    this->modeAButton = new QPushButton("Mode A");
    this->modeBButton = new QPushButton("Mode B");
    generalLayout->addWidget(this->modeAButton);
    generalLayout->addWidget(this->modeBButton);

    this->modeA = new QWidget{};
    this->modeB = new QWidget{};

    //Mode A window
    QVBoxLayout *verticalLayoutModeA = new QVBoxLayout{this->modeA};

    this->goBackModeA = new QPushButton{"Back"};
    verticalLayoutModeA->addWidget(this->goBackModeA);
    // left side - just the list
    this->victimFilesList = new QListWidget{};

    // set the selection model
    this->victimFilesList->setSelectionMode(QAbstractItemView::SingleSelection);
    verticalLayoutModeA->addWidget(this->victimFilesList);

    QWidget *details = new QWidget{};
    QFormLayout *formLayout = new QFormLayout{};
    details->setLayout(formLayout);

    QLabel *labelName = new QLabel{"&Name"};
    this->nameEdit = new QLineEdit{};
    labelName->setBuddy(this->nameEdit);
    formLayout->addRow(labelName, this->nameEdit);

    QLabel *labelPlaceOfOrigin = new QLabel{"&Place of origin"};
    this->placeOfOriginEdit = new QLineEdit{};
    labelPlaceOfOrigin->setBuddy(this->placeOfOriginEdit);
    formLayout->addRow(labelPlaceOfOrigin, this->placeOfOriginEdit);

    QLabel *labelAge = new QLabel{"&Age"};
    this->ageEdit = new QLineEdit{};
    labelAge->setBuddy(this->ageEdit);
    formLayout->addRow(labelAge, this->ageEdit);

    QLabel *labelPhotography = new QLabel{"&Photography"};
    this->photographyEdit = new QLineEdit{};
    labelPhotography->setBuddy(this->photographyEdit);
    formLayout->addRow(labelPhotography, this->photographyEdit);

    verticalLayoutModeA->addWidget(details);

    QWidget *buttons = new QWidget{};
    QHBoxLayout *horizontalLayout = new QHBoxLayout{};
    buttons->setLayout(horizontalLayout);
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->updateButton = new QPushButton{"Update"};
    horizontalLayout->addWidget(this->addButton);
    horizontalLayout->addWidget(this->deleteButton);
    horizontalLayout->addWidget(this->updateButton);

    verticalLayoutModeA->addWidget(buttons);

    QWidget *undo_redo = new QWidget{};
    QHBoxLayout *horizontalLayoutForUndo_Redo = new QHBoxLayout{};
    undo_redo->setLayout(horizontalLayoutForUndo_Redo);
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};
    horizontalLayoutForUndo_Redo->addWidget(this->undoButton);
    horizontalLayoutForUndo_Redo->addWidget(this->redoButton);

    verticalLayoutModeA->addWidget(undo_redo);

    this->shortcutUndo = new QShortcut{QKeySequence(Qt::CTRL + Qt::Key_Z), modeA};
    this->shortcutRedo = new QShortcut{QKeySequence(Qt::CTRL + Qt::Key_Y), modeA};

    //Mode B window
    QVBoxLayout *verticalLayoutModeB = new QVBoxLayout{this->modeB};

    this->goBackModeB = new QPushButton{"Back"};
    verticalLayoutModeB->addWidget(this->goBackModeB);

    this->myList = new QListWidget{};

    this->myList->setSelectionMode(QAbstractItemView::SingleSelection);
    verticalLayoutModeB->addWidget(this->myList);

    QWidget *detailsModeB = new QWidget{};
    QFormLayout *formLayoutModeB = new QFormLayout{};
    detailsModeB->setLayout(formLayoutModeB);

    QLabel *labelAgeFilter = new QLabel{"Age < "};
    this->filterAgeEdit = new QLineEdit{};
    labelName->setBuddy(this->filterAgeEdit);
    formLayoutModeB->addRow(labelAgeFilter, this->filterAgeEdit);

    QLabel *labelPlaceOfOriginFilter = new QLabel{"Place of origin = "};
    this->filterPlaceOfOriginEdit = new QLineEdit{};
    labelPlaceOfOrigin->setBuddy(this->filterPlaceOfOriginEdit);
    formLayoutModeB->addRow(labelPlaceOfOriginFilter, this->filterPlaceOfOriginEdit);

    verticalLayoutModeB->addWidget(detailsModeB);

    this->filterButton = new QPushButton{" Filter "};
    verticalLayoutModeB->addWidget(this->filterButton);

    QWidget *next = new QWidget{};
    QHBoxLayout *horizontalLayoutNext = new QHBoxLayout{};
    next->setLayout(horizontalLayoutNext);
    this->nextButton = new QPushButton{"Next "};
    this->nextEdit = new QLineEdit{};
    horizontalLayoutNext->addWidget(this->nextButton);
    horizontalLayoutNext->addWidget(this->nextEdit);

    verticalLayoutModeB->addWidget(next);

    QWidget *save = new QWidget{};
    QHBoxLayout *horizontalLayoutSave = new QHBoxLayout{};
    save->setLayout(horizontalLayoutSave);
    this->saveButton = new QPushButton{"Save "};
    this->saveEdit = new QLineEdit{};
    horizontalLayoutSave->addWidget(this->saveButton);
    horizontalLayoutSave->addWidget(this->saveEdit);

    verticalLayoutModeB->addWidget(save);

    QWidget *mylist = new QWidget{};
    QHBoxLayout *horizontalLayoutMylist = new QHBoxLayout{};
    mylist->setLayout(horizontalLayoutMylist);
    this->mylistButton = new QPushButton{"Open Mylist"};
    this->mylistWindowButton = new QPushButton{"Open Mylist Table"};
    horizontalLayoutMylist->addWidget(this->mylistButton);
    horizontalLayoutMylist->addWidget(this->mylistWindowButton);

    verticalLayoutModeB->addWidget(mylist);

    this->myListTableModel = new MyListTableModel{this->service};

    QSortFilterProxyModel* proxyModel =
            new QSortFilterProxyModel{};
    proxyModel->setSourceModel(this->myListTableModel);

    this->mylistTableView = new QTableView{};
    this->mylistTableView->setModel(myListTableModel);
    this->mylistTableView->resizeColumnsToContents();
}

void GUI::connectSignalsAndSlots() {
    // when the vector of victimFiles is updated - re-populate the list
    QObject::connect(this, &GUI::updatedSignal, this, &GUI::populateVictimFilesList);

    // add a connection: function listItemChanged() will be called when an item in the list is selected
    QObject::connect(this->victimFilesList, &QListWidget::itemSelectionChanged, this,
                     [this]() { this->listItemChanged(); });

    // mode A buttons connections
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);
    QObject::connect(this->modeAButton, &QPushButton::clicked, this, &GUI::modeAButtonHandler);
    QObject::connect(this->goBackModeA, &QPushButton::clicked, this, &GUI::goBackButtonHandler);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoButtonHandler);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoButtonHandler);
    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &GUI::undoButtonHandler);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &GUI::redoButtonHandler);

    // mode B buttons connections
    QObject::connect(this->modeBButton, &QPushButton::clicked, this, &GUI::modeBButtonHandler);
    QObject::connect(this->goBackModeB, &QPushButton::clicked, this, &GUI::goBackButtonHandler);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextButtonHandler);
    QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveButtonHandler);
    QObject::connect(this->mylistButton, &QPushButton::clicked, this, &GUI::mylistButtonHandler);
    QObject::connect(this->mylistWindowButton, &QPushButton::clicked, this, &GUI::mylistWindowButtonHandler);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
}

void GUI::addButtonHandler() {
    QString name = this->nameEdit->text();
    QString placeOfOrigin = this->placeOfOriginEdit->text();
    QString age = this->ageEdit->text();
    QString photography = this->photographyEdit->text();

    try {
        this->service.addVictim(name.toStdString(), placeOfOrigin.toStdString(),
                                age.toInt(), photography.toStdString());
    }
    catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
    emit updatedSignal();
}

void GUI::deleteButtonHandler() {
    int index = this->getSelectedIndex();

    if (index < 0 || index >= this->service.getVictimFiles().size())
        return;
    try {
        this->service.deleteVictim(this->nameEdit->text().toStdString());
    }
    catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
    emit updatedSignal();
}

void GUI::updateButtonHandler() {
    QString name = this->nameEdit->text();
    QString placeOfOrigin = this->placeOfOriginEdit->text();
    QString age = this->ageEdit->text();
    QString photography = this->photographyEdit->text();
    try {
        this->service.updateVictim(name.toStdString(), placeOfOrigin.toStdString(),
                                   age.toInt(), photography.toStdString());
    }
    catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
    emit updatedSignal();
}

void GUI::populateVictimFilesList() {
    if (this->victimFilesList->count() > 0)
        this->victimFilesList->clear();

    for (auto g : this->service.getVictimFiles()) {
        QString itemInList = QString::fromStdString(g.getSequence());
        QListWidgetItem *item = new QListWidgetItem{itemInList};
        this->victimFilesList->addItem(item);
    }

    // set the selection on the first item in the list
    if (this->service.getVictimFiles().size() > 0)
        this->victimFilesList->setCurrentRow(0);
}

int GUI::getSelectedIndex() {
    if (this->victimFilesList->count() == 0)
        return -1;

    QModelIndexList index = this->victimFilesList->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->nameEdit->clear();
        this->placeOfOriginEdit->clear();
        this->ageEdit->clear();
        this->photographyEdit->clear();
        return -1;
    }

    int i = index.at(0).row();
    return i;
}

void GUI::listItemChanged() {
    int index = this->getSelectedIndex();
    if (index == -1)
        return;

    if (index >= this->service.getVictimFiles().size())
        return;
    VictimFile victimFile = this->service.getVictimFiles()[index];

    this->nameEdit->setText(QString::fromStdString(victimFile.getName()));
    this->placeOfOriginEdit->setText(QString::fromStdString(victimFile.getPlaceOfOrigin()));
    this->ageEdit->setText(QString::fromStdString(to_string(victimFile.getAge())));
    this->photographyEdit->setText(QString::fromStdString(victimFile.getPhotography()));

}

void GUI::modeAButtonHandler() {
    this->hide();
    this->modeA->show();
}

void GUI::modeBButtonHandler() {
    this->hide();
    this->modeB->show();
}

void GUI::goBackButtonHandler() {
    this->modeA->hide();
    this->modeB->hide();
    this->show();
}

void GUI::filterButtonHandler() {
    if (this->myList->count() > 0)
        this->myList->clear();

    if (this->filterAgeEdit->text().toStdString() == ""
        && this->filterPlaceOfOriginEdit->text().toStdString() == "") {
        for (auto g : this->service.getVictimFiles()) {
            QString itemInList = QString::fromStdString(g.getSequence());
            QListWidgetItem *item = new QListWidgetItem{itemInList};
            this->myList->addItem(item);
        }
    }

    if (this->filterAgeEdit->text().toStdString() != ""
        && this->filterPlaceOfOriginEdit->text().toStdString() == "")
        this->filterAge();

    if (this->filterAgeEdit->text().toStdString() == ""
        && this->filterPlaceOfOriginEdit->text().toStdString() != "")
        this->filterPlaceOfOrigin();

    if (this->filterAgeEdit->text().toStdString() != ""
        && this->filterPlaceOfOriginEdit->text().toStdString() != "")
        this->filterAgeAndPlaceOfOrigin();

    if (this->service.getMyList().size() > 0)
        this->myList->setCurrentRow(0);
}

void GUI::filterAge() {
    const vector<VictimFile> repositoryAge = this->service.getVictimFiles();
    auto age = this->filterAgeEdit->text().toInt();
    int numberOfFilesAge = 0;
    for (VictimFile fileAge : repositoryAge) {
        if (fileAge.getAge() < age) {
            this->myList->addItem(QString::fromStdString(fileAge.getSequence()));
            numberOfFilesAge++;
        }
    }
    if (numberOfFilesAge == 0) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "There is no file matching this specification.");
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::filterPlaceOfOrigin() {
    const vector<VictimFile> repository = this->service.getVictimFiles();
    int numberOfFiles = 0;
    auto placeOfOrigin = this->filterPlaceOfOriginEdit->text().toStdString();
    for (VictimFile file : repository) {
        if (file.getPlaceOfOrigin() == placeOfOrigin) {
            this->myList->addItem(QString::fromStdString(file.getSequence()));
            numberOfFiles++;
        }
    }
    if (numberOfFiles == 0) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "There is no file matching this specification.");
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::filterAgeAndPlaceOfOrigin() {
    const vector<VictimFile> repository = this->service.getVictimFiles();
    int numberOfFiles = 0;
    auto placeOfOrigin = this->filterPlaceOfOriginEdit->text().toStdString();
    auto age = this->filterAgeEdit->text().toInt();
    for (VictimFile file : repository) {
        if (file.getPlaceOfOrigin() == placeOfOrigin && file.getAge() < age) {
            this->myList->addItem(QString::fromStdString(file.getSequence()));
            numberOfFiles++;
        }
    }
    if (numberOfFiles == 0) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "There is no file matching this specification.");
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::nextButtonHandler() {
    auto next = this->service.getNext();
    try {
        this->nextEdit->setText(QString::fromStdString(next.getSequence()));
    }
    catch(runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::saveButtonHandler() {
    auto name = this->saveEdit->text();
    try {
        this->service.saveVictimFile(name.toStdString());
    }
    catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::mylistButtonHandler() {
    string file = this->service.getMyListFilesPath();
    string s = "START " + this->service.getMyListFilesPath();
    system(s.c_str());
}

void GUI::undoButtonHandler() {
    try {
        this->service.undo();
        this->updatedSignal();
    } catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::redoButtonHandler() {
    try {
        this->service.redo();
        this->updatedSignal();
    } catch (runtime_error &error) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error.what());
        messageBox.setFixedSize(500, 200);
    }
}

void GUI::mylistWindowButtonHandler() {
    this->mylistTableView->show();
}
