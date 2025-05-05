#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <tuple>
#include <QString>

class Parser {
public:
    // Constructor takes a map number (1-8)
    Parser(int mapNumber);

    std::vector<std::tuple<int, int, char, int, int>> parse();

private:
    int mapNumber;
    QString filePath;

    bool isValidMapNumber(int num);

    std::vector<QString> readFile();

    char getCharAtPosition(const std::vector<QString>& lines, int row, int col);
};

#endif // PARSER_H
