#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Domain.h"


class RepositoryException : public std::runtime_error
{
public:
    RepositoryException(const string &arg) : runtime_error(arg) {}
};


template<typename type>
class Repository {
public:
    virtual void addNewVictim(type element){};

    virtual void updateVictim(type updatedElement, int index){};

    virtual void deleteVictim(int index){};

    virtual void setPath(std::string path) = 0;

    virtual string getPath() = 0;

    virtual const vector<type> getRepository() = 0;

    virtual int getSize() = 0;

    virtual vector<VictimFile> loadRepository() = 0;

    virtual void saveRepository(std::vector<type> elementsArray) = 0;
};