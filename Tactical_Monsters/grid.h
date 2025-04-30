#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include "utils/fileparser.h"

class Grid {
public:
    Grid(QGraphicsScene* scene);
    void loadMap(const QString& path);

private:
    QGraphicsScene* m_scene;
};

#endif // GRID_H
