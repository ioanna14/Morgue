
#pragma once

#include <string>

#include "FileRepository.h"
#include "Domain.h"
#include "Action.h"

using namespace std;

class Service {
public:

    Service(Repository<VictimFile> *repository, Repository<VictimFile> *mylist);


    virtual ~Service();
    /*
    Adds a new victim file to the array of victim's files.
    */
    void addVictim(string name, string placeOfOrigin, int age, string photography);

    /*
    Updates a certain victim file with new information about the place of origin,
     the age and the photo.
    */
    void updateVictim(string name, string newPlaceOfOrigin, int newAge, string newPhotography);

    /*
    Deletes a certain victim file from the array of files.
    */
    void deleteVictim(string name);

    /*
    Returns a copy of the array with the objects from the repository.
    */
    vector<VictimFile> getVictimFiles() const;


    /*
     Returns the next victim file from the list.
     */
    VictimFile getNext();

    /*
    Adds a new element to myList.
    */
    void saveVictimFile(string name);

    /*
     Sets the path.
     */
    void setVictimFilesPath(string path);

    /*
     Returns the path.
     */
    string getVictimFilesPath();

    /*
     Sets the path of mylist.
     */
    void setMyListPath(string path);

    /*
     Returns the path of mylist.
     */
    string getMyListFilesPath();

    std::vector<VictimFile> getMyList() const;

    void undo();

    void redo();

private:
    vector<Action *> undoStack;
    vector<Action *> redoStack;
    int indexOfIteration = 0;
    Repository<VictimFile> *repository;
    Repository<VictimFile> *myList;
};