#include <iostream>
#include <fstream>
#include "gtr_parser.h"
#include "xml_parser.h"
#include "gtr_parser.cpp"
#include "xml_parser.cpp"

using namespace std;

void createGTRFile(const string &fileName)
{
    ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        cout << "Не вдалося відкрити файл для запису.\n";
        return;
    }

    string name, surname, gender, birthdate;
    cout << "Введіть ім'я: ";
    cin >> name;
    cout << "Введіть прізвище: ";
    cin >> surname;
    cout << "Введіть стать: ";
    cin >> gender;
    cout << "Введіть дату народження (YYYY-MM-DD): ";
    cin >> birthdate;

    outFile << "1 NAME " << name << endl;
    outFile << "1 SURNAME " << surname << endl;
    outFile << "1 GENDER " << gender << endl;
    outFile << "1 BIRTHDATE " << birthdate << endl;

    outFile.close();
    cout << "Файл " << fileName << " успішно створено.\n";
}

int main()
{
    while (true)
    {
        cout << "Оберіть режим:\n";
        cout << "1. Конвертація GTR в XML\n";
        cout << "2. Конвертація XML в GTR\n";
        cout << "3. Створити файл GTR\n";
        cout << "4. Вихід\n";
        cout << "Введіть ваш вибір: ";
        int choice;
        cin >> choice;

        if (choice == 4)
        {
            break;
        }

        string inputFileName, outputFileName;

        if (choice == 1 || choice == 2)
        {
            cout << "Введіть ім'я вхідного файлу: ";
            cin >> inputFileName;
            cout << "Введіть ім'я вихідного файлу: ";
            cin >> outputFileName;
        }

        switch (choice)
        {
        case 1:
            convertGTRToXML(inputFileName, outputFileName);
            break;
        case 2:
            convertXMLToGTR(inputFileName, outputFileName);
            break;
        case 3:
            cout << "Введіть ім'я файлу для створення: ";
            cin >> inputFileName;
            createGTRFile(inputFileName);
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}