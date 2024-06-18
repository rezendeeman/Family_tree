#include <iostream>
#include <fstream>
#include "gtr_parser.h"
#include "xml_parser.h"
#include "gtr_parser.cpp"
#include "xml_parser.cpp"

using namespace std;

void createGTRFileFromConsole(const string &fileName)
{
    ofstream outfile(fileName);
    if (outfile.is_open())
    {
        string name, surname, gender, birthdate;
        cout << "Введіть ім'я: ";
        cin >> name;
        outfile << "1 NAME " << name << "\n";

        cout << "Введіть прізвище: ";
        cin >> surname;
        outfile << "1 SURNAME " << surname << "\n";

        cout << "Введіть стать (M/F): ";
        cin >> gender;
        outfile << "1 GENDER " << gender << "\n";

        cout << "Введіть дату народження (YYYY-MM-DD): ";
        cin >> birthdate;
        outfile << "1 BIRTHDATE " << birthdate << "\n";

        char moreChildren;
        int childLevel = 2;
        do
        {
            cout << "Додати дитину? (y/n): ";
            cin >> moreChildren;
            if (moreChildren == 'y' || moreChildren == 'Y')
            {
                cout << "Введіть ім'я дитини: ";
                cin >> name;
                outfile << childLevel << " NAME " << name << "\n";

                cout << "Введіть прізвище дитини: ";
                cin >> surname;
                outfile << childLevel << " SURNAME " << surname << "\n";

                cout << "Введіть стать дитини (M/F): ";
                cin >> gender;
                outfile << childLevel << " GENDER " << gender << "\n";

                cout << "Введіть дату народження дитини (YYYY-MM-DD): ";
                cin >> birthdate;
                outfile << childLevel << " BIRTHDATE " << birthdate << "\n";
            }
        } while (moreChildren == 'y' || moreChildren == 'Y');

        outfile.close();
        cout << "Файл " << fileName << " створено.\n";
    }
    else
    {
        cerr << "Неможливо відкрити файл " << fileName << " для запису.\n";
    }
}

void createXMLFileFromConsole(const string &fileName)
{
    ofstream outfile(fileName);
    if (outfile.is_open())
    {
        string name, surname, gender, birthdate;
        cout << "Введіть ім'я: ";
        cin >> name;
        cout << "Введіть прізвище: ";
        cin >> surname;
        cout << "Введіть стать (M/F): ";
        cin >> gender;
        cout << "Введіть дату народження (YYYY-MM-DD): ";
        cin >> birthdate;

        outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        outfile << "<family_tree>\n";
        outfile << "    <person name=\"" << name << "\" surname=\"" << surname << "\" gender=\"" << gender << "\" birthdate=\"" << birthdate << "\">\n";

        char moreChildren;
        do
        {
            cout << "Додати дитину? (y/n): ";
            cin >> moreChildren;
            if (moreChildren == 'y' || moreChildren == 'Y')
            {
                cout << "Введіть ім'я дитини: ";
                cin >> name;
                cout << "Введіть прізвище дитини: ";
                cin >> surname;
                cout << "Введіть стать дитини (M/F): ";
                cin >> gender;
                cout << "Введіть дату народження дитини (YYYY-MM-DD): ";
                cin >> birthdate;

                outfile << "        <person name=\"" << name << "\" surname=\"" << surname << "\" gender=\"" << gender << "\" birthdate=\"" << birthdate << "\">\n";
                outfile << "        </person>\n";
            }
        } while (moreChildren == 'y' || moreChildren == 'Y');

        outfile << "    </person>\n";
        outfile << "</family_tree>\n";
        outfile.close();
        cout << "Файл " << fileName << " створено.\n";
    }
    else
    {
        cerr << "Неможливо відкрити файл " << fileName << " для запису.\n";
    }
}

int main()
{
    cout << "Виберіть режим роботи:\n";
    cout << "1. Конвертація з GTR в XML\n";
    cout << "2. Конвертація з XML в GTR\n";
    cout << "3. Створити зразковий GTR файл\n";
    cout << "4. Створити зразковий XML файл\n";

    int choice;
    cin >> choice;

    string inputFileName, outputFileName;

    switch (choice)
    {
    case 1:
        cout << "Введіть ім'я вхідного GTR файлу: ";
        cin >> inputFileName;
        cout << "Введіть ім'я вихідного XML файлу: ";
        cin >> outputFileName;
        convertGTRToXML(inputFileName, outputFileName);
        // break;
    case 2:
        cout << "Введіть ім'я вхідного XML файлу: ";
        cin >> inputFileName;
        cout << "Введіть ім'я вихідного GTR файлу: ";
        cin >> outputFileName;
        convertXMLToGTR(inputFileName, outputFileName);
        break;
    case 3:
        cout << "Введіть ім'я зразкового GTR файлу: ";
        cin >> inputFileName;
        createGTRFileFromConsole(inputFileName);
        break;
    case 4:
        cout << "Введіть ім'я зразкового XML файлу: ";
        cin >> inputFileName;
        createXMLFileFromConsole(inputFileName);
        break;
    default:
        cout << "Невірний вибір. Програма завершує роботу.\n";
        break;
    }

    return 0;
}
