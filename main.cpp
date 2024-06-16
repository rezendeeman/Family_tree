#include <iostream>
#include "gtr_parser.h"
#include "xml_parser.h"

using namespace std;

int main() {
    while (true) {
        cout << "Оберіть режим:\n";
        cout << "1. Конвертація GTR в XML\n";
        cout << "2. Конвертація XML в GTR\n";
        cout << "3. Вихід\n";
        cout << "Введіть ваш вибір: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            break;
        }

        string inputFileName, outputFileName;
        cout << "Введіть ім'я вхідного файлу: ";
        cin >> inputFileName;
        cout << "Введіть ім'я вихідного файлу: ";
        cin >> outputFileName;

        if (choice == 1) {
            convertGTRToXML(inputFileName, outputFileName);
            break;
        } else if (choice == 2) {
            convertXMLToGTR(inputFileName, outputFileName);
            break;
        } else {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}
