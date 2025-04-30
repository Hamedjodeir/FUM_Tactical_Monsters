#include "fileparser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

QVector<QStringList> FileParser::parseMap(const QString& resourcePath) {
    QVector<QStringList> parsedData;

    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file:" << resourcePath;
        return parsedData;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QStringList tiles = line.split(' ', Qt::SkipEmptyParts);
            parsedData.append(tiles);
        }
    }

    file.close();
    return parsedData;
}
