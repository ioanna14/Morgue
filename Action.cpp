#include "Action.h"

AddAction::AddAction(const VictimFile &addedVictim,
                     Repository<VictimFile> *repo) :
        addedVictim(addedVictim),
        repository(repo) {}

void AddAction::undo() {
    int index = 0;
    for (const auto &file : this->repository->getRepository()) {
        if (file.getName() == this->addedVictim.getName()) {
            this->repository->deleteVictim(index);
            break;
        }
        index++;
    }
}

void AddAction::redo() {
    this->repository->addNewVictim(this->addedVictim);
}

RemoveAction::RemoveAction(const VictimFile &removedVictim,
                           Repository<VictimFile> *repo) :
        removedVictim(removedVictim),
        repository(repo) {}

void RemoveAction::undo() {
    this->repository->addNewVictim(this->removedVictim);
}

void RemoveAction::redo() {
    int index = 0;
    for (const auto &file : this->repository->getRepository()) {
        if (file.getName() == this->removedVictim.getName()) {
            this->repository->deleteVictim(index);
            break;
        }
        index++;
    }
}

UpdateAction::UpdateAction(const VictimFile &updatedVictim,
                           const VictimFile &oldVictim,
                           Repository<VictimFile> *repo)
        : updatedVictim(updatedVictim),
          oldVictim(oldVictim),
          repository(repo) {}

void UpdateAction::undo() {
    int index = 0;
    for (const auto &file : this->repository->getRepository()) {
        if (file.getName() == this->oldVictim.getName()) {
            this->repository->updateVictim(this->oldVictim, index);
            break;
        }
        index++;
    }
}

void UpdateAction::redo() {
    int index = 0;
    for (const auto &file : this->repository->getRepository()) {
        if (file.getName() == this->updatedVictim.getName()) {
            this->repository->updateVictim(this->updatedVictim, index);
            break;
        }
        index++;
    }
}
