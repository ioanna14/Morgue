
#include "Service.h"
#include "HTMLRepository.h"
#include "CSVRepository.h"
#include <map>

using namespace std;

Service::Service(Repository<VictimFile> *repository, Repository<VictimFile> *mylist) :
        repository(repository), myList(mylist) {}

vector<VictimFile> Service::getVictimFiles() const {
    return this->repository->getRepository();
}

void Service::addVictim(string name, string placeOfOrigin, int age, string photography) {
    VictimFile newVictimFile = VictimFile(name, placeOfOrigin, age, photography);
    bool test = false;
    for (auto file:this->getVictimFiles()) {
        if (file == newVictimFile)
            test = true;
    }
    if (!test) {
        this->repository->addNewVictim(newVictimFile);
        Action *addAction = new AddAction(newVictimFile, this->repository);
        this->undoStack.push_back(addAction);
    } else
        throw std::runtime_error("The file already exists!");
}

void Service::updateVictim(string name, string newPlaceOfOrigin, int newAge, string newPhotography) {
    VictimFile updatedVictimFile;
    VictimFile oldVictimFile;
    int index = 0;
    bool test = false;
    for (const auto &file : this->getVictimFiles()) {
        if (file.getName() == name) {
            oldVictimFile = VictimFile(name, file.getPlaceOfOrigin(), file.getAge(), file.getPhotography());
            updatedVictimFile = VictimFile(name, newPlaceOfOrigin, newAge, newPhotography);
            this->repository->updateVictim(updatedVictimFile, index);
            Action *updateAction = new UpdateAction(updatedVictimFile, oldVictimFile, this->repository);
            this->undoStack.push_back(updateAction);
            test = true;
            break;
        }
        index++;
    }
    if (!test)
        throw std::runtime_error("The file does not exists!");
}

void Service::deleteVictim(string name) {
    int index = 0;
    bool test = false;
    for (const auto &file : this->getVictimFiles()) {
        if (file.getName() == name) {
            this->repository->deleteVictim(index);
            Action *removeAction = new RemoveAction(file, this->repository);
            this->undoStack.push_back(removeAction);
            test = true;
            break;
        }
        index++;
    }
    if (!test)
        throw std::runtime_error("The file does not exists!");
}

VictimFile Service::getNext() {
    this->repository->loadRepository();
    if (this->repository->getSize() == 0) {
        throw std::runtime_error("The list is empty!");
    } else {
        if (indexOfIteration < this->repository->getSize())
            return this->getVictimFiles().at(indexOfIteration++);
        else {
            indexOfIteration = 0;
            return this->repository->getRepository().at(indexOfIteration++);
        }
    }
}

void Service::saveVictimFile(string name) {
    VictimFile newVictim;
    for (const auto &file : this->repository->getRepository()) {
        if (file.getName() == name) {
            newVictim = file;
            break;
        }
    }
    if (newVictim == VictimFile())
        throw std::runtime_error("There is no file to save!");
    this->myList->addNewVictim(newVictim);
}

void Service::setVictimFilesPath(string path) {
    this->repository->setPath(path);

}

string Service::getVictimFilesPath() {
    return this->repository->getPath();
}

void Service::setMyListPath(string path) {
    string file = path;
    file.erase(0, file.find('.') + 1);
    if (file == "html")
        myList = new HTMLRepository<VictimFile>();
    if (file == "csv")
        myList = new CSVRepository<VictimFile>();
    this->myList->setPath(path);
}

string Service::getMyListFilesPath() {
    return this->myList->getPath();
}

std::vector<VictimFile> Service::getMyList() const {
    return this->myList->getRepository();
}

Service::~Service() {
    //delete myList;
    this->myList = nullptr;
}

void Service::undo() {
    if (this->undoStack.empty())
        throw runtime_error("No more undoes!");
    Action *action = undoStack.back();
    undoStack.pop_back();
    action->undo();
    redoStack.push_back(action);
}

void Service::redo() {
    if (this->redoStack.empty())
        throw runtime_error("No more redoes!");
    Action *action = redoStack.back();
    redoStack.pop_back();
    action->redo();
    undoStack.push_back(action);
}
