#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Domain.h"
#include "MainRepository.h"

template<typename type>
class FileRepository : public Repository<type> {
protected:
    string path;

public:
    FileRepository();

    void addNewVictim(type element) override;

    void updateVictim(type updatedElement, int index) override;

    void deleteVictim(int index) override;

    void setPath(std::string path) override;

    string getPath() override;

    const vector<type> getRepository() override;

    int getSize() override;

    std::vector<type> loadRepository() override;

    void saveRepository(std::vector<type> elementsArray) override ;
};

template<typename type>
std::vector<type> FileRepository<type>::loadRepository() {
    std::ifstream fileInput(path);
    std::vector<type> elementsArray;
    if (fileInput.is_open()) {
        type object;
        while (fileInput >> object) {
            if (object.getName() != "")
                elementsArray.push_back(object);
        }
        fileInput.close();
    }
    return elementsArray;
}

template<typename type>
void FileRepository<type>::saveRepository(std::vector<type> elementsArray) {
    std::ofstream fileOutput(path);
    if (fileOutput.is_open()) {
        while (elementsArray.size() > 0) {
            auto object = elementsArray.back();
            elementsArray.pop_back();
            fileOutput << object;
        }
        fileOutput.close();
    } else
        throw std::runtime_error("The file is not opening!");
}

template<typename type>
void FileRepository<type>::addNewVictim(type element) {
    std::vector<type> elementsArray = this->loadRepository();
    elementsArray.push_back(element);
    this->saveRepository(elementsArray);
}

template<typename type>
void FileRepository<type>::updateVictim(type updatedElement, int index) {
    std::vector<type> elementsArray = this->loadRepository();
    elementsArray.at(index) = updatedElement;
    this->saveRepository(elementsArray);
}

template<typename type>
void FileRepository<type>::deleteVictim(int index) {
    std::vector<type> elementsArray = this->loadRepository();
    elementsArray.erase(elementsArray.begin() + index);
    this->saveRepository(elementsArray);
}

template<typename type>
void FileRepository<type>::setPath(std::string path) {
    this->path = path;
}

template<typename type>
const vector<type> FileRepository<type>::getRepository() {
    return this->loadRepository();
}

template<typename type>
int FileRepository<type>::getSize() {
    return loadRepository().size();
}

template<typename type>
string FileRepository<type>::getPath() {
    return this->path;
}

template<typename type>
FileRepository<type>::FileRepository() = default;
