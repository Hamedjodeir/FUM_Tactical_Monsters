#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include <QStringList>
#include <QVector>

class FileParser {
public:
    QVector<QStringList> parseMap(const QString& resourcePath);
};

#endif // FILEPARSER_H
