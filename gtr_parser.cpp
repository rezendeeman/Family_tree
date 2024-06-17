#include "gtr_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

void parseGTR(const vector<string>& lines, vector<Person>& people, int& index, int level = 1) {
    Person currentPerson;
    int currentLevel = level;

    while (index < lines.size()) {
        string line = lines[index];
        istringstream iss(line);
        int personLevel;
        string tag, data;
        iss >> personLevel >> tag;
        getline(iss, data);

        if (!data.empty() && data[0] == ' ') {
            data = data.substr(1);
        }

        if (personLevel > currentLevel) {
            parseGTR(lines, currentPerson.children, index, personLevel);
        } else if (personLevel < currentLevel) {
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
            ++index;
        }
    }
    people.push_back(currentPerson);
}

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

    vector<string> lines;
    string line;
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();

    vector<Person> people;
    int index = 0;
    parseGTR(lines, people, index);

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
