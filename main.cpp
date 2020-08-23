#include "Service.h"
#include "HTMLRepository.h"
#include "CSVRepository.h"
#include <QtWidgets>
#include <QApplication>
#include "GUI.h"
#include <fstream>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    ifstream in("../setari.txt");
    if (!in.is_open()) {
        return 0;
    }

    std::string typeRepository;
    in >> typeRepository;

    std::string pathRepository;
    in >> pathRepository;

    std::string typeMyList;
    in >> typeMyList;

    std::string pathMyList;
    in >> pathMyList;

    Repository<VictimFile>* repository;
    if (typeMyList == "html") {
        repository = new HTMLRepository<VictimFile>;
        repository->setPath(pathRepository);
    }
    if (typeMyList == "csv") {
        repository = new CSVRepository<VictimFile>;
        repository->setPath(pathRepository);
    }
    if (typeRepository == "file") {
        repository = new FileRepository<VictimFile>;
        repository->setPath(pathRepository);
    }

    Repository<VictimFile> *mylist;
    if (typeMyList == "html") {
        mylist = new HTMLRepository<VictimFile>;
        mylist->setPath(pathMyList);
    }
    if (typeMyList == "csv") {
        mylist = new CSVRepository<VictimFile>;
        mylist->setPath(pathMyList);
    }

    GUI gui{Service(repository, mylist)};
    gui.show();

    return application.exec();
}
