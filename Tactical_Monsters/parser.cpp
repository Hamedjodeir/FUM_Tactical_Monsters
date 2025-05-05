#include "parser.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include <QDebug>

Parser::Parser(int mapNumber) : mapNumber(mapNumber) {
    if (!isValidMapNumber(mapNumber)) {
        throw std::invalid_argument("Map number must be between 1 and 8");
    }
    filePath = QString(":/Assets/maps/grid%1.txt").arg(mapNumber);
}

bool Parser::isValidMapNumber(int num) {
    return num >= 1 && num <= 8;
}

std::vector<QString> Parser::readFile() {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        throw std::runtime_error("Could not open file: " + filePath.toStdString());
    }

    std::vector<QString> lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        lines.push_back(in.readLine());
    }

    file.close();
    return lines;
}

char Parser::getCharAtPosition(const std::vector<QString>& lines, int row, int col) {
    if (row < 0 || row >= static_cast<int>(lines.size())) {
        return ' ';
    }

    if (col < 0 || col >= lines[row].length()) {
        return ' ';
    }

    return lines[row][col].toLatin1();
}

std::vector<std::tuple<int, int, char, int, int>> Parser::parse() {
    auto lines = readFile();
    std::vector<std::tuple<int, int, char, int, int>> result;

    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 9; ++y) {
            int rowOfTxt, colOfTxt;

            if (y % 2 == 0) {
                rowOfTxt = 2 * x + 1;
                colOfTxt = 3 * y + 1;
            } else {
                rowOfTxt = 2 * x + 2;
                colOfTxt = 3 * y + 1;
            }

            char z = getCharAtPosition(lines, rowOfTxt, colOfTxt);

            if (z == '1' || z == '2' || z == '~' || z == '#') {
                result.emplace_back(x, y, z, 0, 0);
            }
        }
    }

    return result;
}
