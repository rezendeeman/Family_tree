#include "xml_parser.h"
#include <fstream>
#include <iostream>

using namespace std;

void parseXML(ifstream& infile, vector<Person>& people, int level = 1) {
    string line;
    while (getline(infile, line)) {
        if (line.find("<person") != string::npos) {
            Person person;
            size_t pos = line.find("name=\"");
            if (pos != string::npos) {
                size_t end = line.find("\"", pos + 6);
                person.name = line.substr(pos + 6, end - pos - 6);
            }
            pos = line.find("surname=\"");
            if (pos != string::npos) {
                size_t end = line.find("\"", pos + 9);
                person.surname = line.substr(pos + 9, end - pos - 9);
            }
            pos = line.find("gender=\"");
            if (pos != string::npos) {
                size_t end = line.find("\"", pos + 8);
                person.gender = line.substr(pos + 8, end - pos - 8);
            }
            pos = line.find("birthdate=\"");
            if (pos != string::npos) {
                size_t end = line.find("\"", pos + 11);
                person.birthdate = line.substr(pos + 11, end - pos - 11);
            }
            parseXML(infile, person.children, level + 1);
            people.push_back(person);
        } else if (line.find("</person>") != string::npos) {
            break;
        }
    }
}

void writeGTR(ofstream& outfile, const vector<Person>& people, int level = 1) {
    for (const auto& person : people) {
        outfile << level << " NAME " << person.name << "\n";
        outfile << level << " SURNAME " << person.surname << "\n";
        outfile << level << " GENDER " << person.gender << "\n";
        outfile << level << " BIRTHDATE " << person.birthdate << "\n";
        if (!person.children.empty()) {
            writeGTR(outfile, person.children, level + 1);
        }
    }
}

void convertXMLToGTR(const string& inputFileName, const string& outputFileName) {
    ifstream infile(inputFileName);
    if (!infile.is_open()) {
        cerr << "Неможливо відкрити файл " << inputFileName << "\n";
        return;
    }

    vector<Person> people;
    parseXML(infile, people);
    infile.close();

    ofstream outfile(outputFileName);
    if (!outfile.is_open()) {
        cerr << "Неможливо відкрити файл " << outputFileName << "\n";
        return;
    }

    writeGTR(outfile, people);
    outfile.close();

    cout << "Конвертація з " << inputFileName << " в " << outputFileName << " успішно виконана.\n";
}
