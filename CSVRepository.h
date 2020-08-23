#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Domain.h"
#include "FileRepository.h"

template<typename type>
class CSVRepository :public FileRepository<type>{
public:
    void addNewVictim(type element) override;

    void updateVictim(type updatedElement, int index) override;

    void deleteVictim(int index) override;

    void setPath(std::string path) override;

    string getPath() override;

    const vector<type> getRepository() override;

    int getSize() override;

    vector<type> loadRepository() override;

    void saveRepository(std::vector<type> elementsArray) override;
};

template<typename type>
void CSVRepository<type>::addNewVictim(type element) {
    FileRepository<type>::addNewVictim(element);
}

template<typename type>
void CSVRepository<type>::updateVictim(type updatedElement, int index) {
    FileRepository<type>::updateVictim(updatedElement, index);
}

template<typename type>
void CSVRepository<type>::deleteVictim(int index) {
    FileRepository<type>::deleteVictim(index);
}

template<typename type>
void CSVRepository<type>::setPath(std::string path) {
    FileRepository<type>::setPath(path);
}

template<typename type>
string CSVRepository<type>::getPath() {
    return FileRepository<type>::getPath();
}

template<typename type>
const vector<type> CSVRepository<type>::getRepository() {
    return FileRepository<type>::getRepository();
}

template<typename type>
int CSVRepository<type>::getSize() {
    return FileRepository<type>::getSize();
}

template<typename type>
std::vector<type> CSVRepository<type>::loadRepository() {
    std::ifstream fileInput(this->path);
    std::vector<type> elementsArray;
    if (fileInput.is_open()) {
        type object;
        while (inCSV(fileInput, object)){
            if (object.getName() != "")
                elementsArray.push_back(object);
        }
        fileInput.close();
    }
    return elementsArray;
}

template<typename type>
void CSVRepository<type>::saveRepository( std::vector<type> elementsArray) {
    std::ofstream fileOutput(this->path);
    if (fileOutput.is_open()) {
        while (elementsArray.size() > 0) {
            auto object = elementsArray.back();
            elementsArray.pop_back();
            outCSV(fileOutput, object);
        }
        fileOutput.close();
    } else
        throw std::runtime_error("The file is not opening!");
}
