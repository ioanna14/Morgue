//
// Created by Ioana on 5/28/2020.
//

#ifndef MORGUE_ACTION_H
#define MORGUE_ACTION_H


#include "Domain.h"
#include "MainRepository.h"

class Action {
public:
    virtual void undo() = 0;

    virtual void redo() = 0;
};


class AddAction : public Action {
private:
    VictimFile addedVictim;
    Repository<VictimFile> *repository;
public:
    void undo() override;

    AddAction(const VictimFile &addedVictim, Repository<VictimFile> *repo);

    void redo() override;
};


class RemoveAction : public Action {
private:
public:
    RemoveAction(const VictimFile &removedVictim, Repository<VictimFile> *repo);

private:
    VictimFile removedVictim;
    Repository<VictimFile> *repository;
public:
    void undo() override;

    void redo() override;

};


class UpdateAction : public Action {
private:
public:
    UpdateAction(const VictimFile &updatedVictim, const VictimFile &oldVictim,
                 Repository<VictimFile> *repo);

private:
    VictimFile updatedVictim;
    VictimFile oldVictim;
    Repository<VictimFile> *repository;
public:
    void undo() override;

    void redo() override;

};


#endif //MORGUE_ACTION_H
