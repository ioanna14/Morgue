#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Domain.h"
#include "FileRepository.h"

template<typename type>
class HTMLRepository : public FileRepository<type>{
public:
    vector<type> loadRepository() override;

    void addNewVictim(type element) override;

    void updateVictim(type updatedElement, int index) override;

    void deleteVictim(int index) override;

    void setPath(std::string path) override;

    string getPath() override;

    const vector<type> getRepository() override;

    int getSize() override;

    void saveRepository(std::vector<type> elementsArray) override;
};

template<typename type>
std::vector<type> HTMLRepository<type>::loadRepository() {
    std::ifstream fileInput(this->path);
    if (fileInput.is_open()) {
        std::vector<type> elementsArray;
        string line;
        int numberOfLines = 0;
        while (numberOfLines < 10) {
            getline(fileInput, line);
            if (line.empty()){
                return elementsArray;
            }
            numberOfLines++;
        }
        while (getline(fileInput, line)) {
            if (line == "</table>")
                break;
            type object;
            inHTML(fileInput, object);
            elementsArray.push_back(object);
            getline(fileInput, line);
        }
        fileInput.close();
        return elementsArray;
    }
    return std::vector<type>();
}

template<typename type>
void HTMLRepository<type>::saveRepository(std::vector<type> elementsArray) {
    std::ofstream fileOutput(this->path);
    if (fileOutput.is_open()) {
        fileOutput << "<!DOCTYPE html>\n" <<
                   "<html>\n" <<
                   "<body>\n" <<
                   "<table border=\"1\">\n" <<
                   "<tr>\n" <<
                   "<td>Name</td>\n" <<
                   "<td>Place Of Origin</td>\n" <<
                   "<td>Age</td>\n" <<
                   "<td>Photography</td>\n" <<
                   "</tr>\n";
        while (elementsArray.size() > 0) {
            fileOutput << "<tr>\n";
            auto object = elementsArray.back();
            elementsArray.pop_back();
            outHTML(fileOutput, object);
            fileOutput << "</tr>\n";
        }
        fileOutput << "</table>\n"
                      "</body>\n"
                      "</html>";
        fileOutput.close();
    } else {
        throw std::runtime_error("The file is not opening!");
    }
}

template<typename type>
void HTMLRepository<type>::addNewVictim(type element) {
    FileRepository<type>::addNewVictim(element);
}

template<typename type>
void HTMLRepository<type>::updateVictim(type updatedElement, int index) {
    FileRepository<type>::updateVictim(updatedElement, index);
}

template<typename type>
void HTMLRepository<type>::deleteVictim(int index) {
    FileRepository<type>::deleteVictim(index);
}

template<typename type>
void HTMLRepository<type>::setPath(std::string path) {
    FileRepository<type>::setPath(path);
}

template<typename type>
string HTMLRepository<type>::getPath() {
    return FileRepository<type>::getPath();
}

template<typename type>
const vector<type> HTMLRepository<type>::getRepository() {
    return FileRepository<type>::getRepository();
}

template<typename type>
int HTMLRepository<type>::getSize() {
    return FileRepository<type>::getSize();
}

