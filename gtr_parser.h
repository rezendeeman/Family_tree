#ifndef GTR_PARSER_H
#define GTR_PARSER_H

#include <vector>
#include <string>

struct Person {
    std::string name;
    std::string surname;
    std::string gender;
    std::string birthdate;
    std::vector<Person> children;
};

void convertGTRToXML(const std::string& inputFileName, const std::string& outputFileName);

#endif // GTR_PARSER_H
