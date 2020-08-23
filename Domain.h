#pragma once

#include <fstream>
#include <string>

using namespace std;

class VictimFile {
public:
    VictimFile(string name,
               string placeOfOrigin,
               int age,
               string photography) :
            name(name),
            placeOfOrigin(placeOfOrigin),
            age(age),
            photography(photography) {};

    VictimFile() {}

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        VictimFile::name = name;
    }

    const string &getPlaceOfOrigin() const {
        return placeOfOrigin;
    }

    void setPlaceOfOrigin(const string &placeOfOrigin) {
        VictimFile::placeOfOrigin = placeOfOrigin;
    }

    int getAge() const {
        return age;
    }

    string getSequence() {
        return this->getName() + ", " + this->getPlaceOfOrigin() + ", "
                + to_string(this->getAge()) + ", " + this->getPhotography();
    }

    void setAge(int age) {
        VictimFile::age = age;
    }

    const string &getPhotography() const {
        return photography;
    }

    void setPhotography(const string &photography) {
        VictimFile::photography = photography;
    }

    void operator=(VictimFile other) {
        this->name = other.name;
        this->placeOfOrigin = other.placeOfOrigin;
        this->age = other.age;
        this->photography = other.photography;
    }

    bool operator==(VictimFile other) {
        return this->name == other.name;
    }

    friend ostream &operator<<(ostream &out, VictimFile &file) {
        out << file.name << " " << file.placeOfOrigin << " "
            << to_string(file.age) << " " << file.photography << "\n";
        return out;
    }

    friend istream &operator>>(istream &in, VictimFile &file) {
        in >> file.name >> file.placeOfOrigin >> file.age >> file.photography;
        return in;
    }

    friend ostream &outCSV(ostream &out, VictimFile &file) {
        out << file.name << "," << file.placeOfOrigin << ","
            << to_string(file.age) << "," << file.photography << "\n";
        return out;
    }

    friend istream &inCSV(istream &in, VictimFile &file) {
        std::string input;
        getline(in, input);
        if(input.empty()){
            return in;
        }
        file.name = input.substr(0, input.find(','));
        input.erase(0, input.find(',') + 1);
        file.placeOfOrigin = input.substr(0, input.find(','));
        input.erase(0, input.find(',') + 1);
        file.age = stoi(input.substr(0, input.find(',')));
        input.erase(0, input.find(',') + 1);
        file.photography = input.substr(0, input.find(','));
        input.erase(0, input.find(',') + 1);
        return in;
    }

    friend istream &inHTML(istream &in, VictimFile &file) {
        std::string input;
        getline(in, input);
        input.erase(0, 4);
        file.name = input.substr(0, input.find("</td>"));
        getline(in, input);
        input.erase(0, 4);
        file.placeOfOrigin = input.substr(0, input.find("</td>"));
        getline(in, input);
        input.erase(0, 4);
        file.age = stoi(input.substr(0, input.find("</td>")));
        getline(in, input);
        input.erase(0, 4);
        file.photography = input.substr(0, input.find("</td>"));
        return in;
    }

    friend ostream &outHTML(ostream &out, VictimFile &file) {
        out << "<td>" << file.name << "</td>" << "\n"
            << "<td>" << file.placeOfOrigin << "</td>" << "\n"
            << "<td>" << to_string(file.age) << "</td>" << "\n"
            << "<td>" << file.photography << "</td>" << "\n";
        return out;
    }

private:
    string name;
    string placeOfOrigin;
    int age;
    string photography;
};

