#include "gtr_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Функція для парсингу файлу формату .gtr
void parseGTR(ifstream& infile, vector<Person>& people, int level = 1) {
    string line;
    Person currentPerson;
    int currentLevel = level;
    while (getline(infile, line)) {
        istringstream iss(line);
        int personLevel;
        string tag, data;
        iss >> personLevel >> tag;
        getline(iss, data);
        data = data.substr(1); // Видалення пробілу
        
        if (personLevel > currentLevel) {
            infile.seekg(-line.length() - 1, ios_base::cur);
            parseGTR(infile, currentPerson.children, personLevel);
        } else if (personLevel < currentLevel) {
            infile.seekg(-line.length() - 1, ios_base::cur);
            break;
        } else {
            if (tag == "NAME") {
                currentPerson.name = data;
            } else if (tag == "SURNAME") {
                currentPerson.surname = data;
            } else if (tag == "GENDER") {
                currentPerson.gender = data;
            } else if (tag == "BIRTHDATE") {
                currentPerson.birthdate = data;
            }
        }
    }
    people.push_back(currentPerson);
}

// Функція для запису даних у форматі XML
void writeXML(ofstream& outfile, const vector<Person>& people, int indent = 1) {
    string indentStr(indent, '\t');
    for (const auto& person : people) {
        outfile << indentStr << "<person name=\"" << person.name << "\" "
                << "surname=\"" << person.surname << "\" "
                << "gender=\"" << person.gender << "\" "
                << "birthdate=\"" << person.birthdate << "\">\n";
        if (!person.children.empty()) {
            writeXML(outfile, person.children, indent + 1);
        }
        outfile << indentStr << "</person>\n";
    }
}

void convertGTRToXML(const string& inputFileName, const string& outputFileName) {
    ifstream infile(inputFileName);
    if (!infile.is_open()) {
        cerr << "Неможливо відкрити файл " << inputFileName << "\n";
        return;
    }

    vector<Person> people;
    parseGTR(infile, people);
    infile.close();

    ofstream outfile(outputFileName);
    if (!outfile.is_open()) {
        cerr << "Неможливо відкрити файл " << outputFileName << "\n";
        return;
    }

    outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    outfile << "<family_tree>\n";
    writeXML(outfile, people);
    outfile << "</family_tree>\n";
    outfile.close();

    cout << "Конвертація з " << inputFileName << " в " << outputFileName << " успішно виконана.\n";
}
