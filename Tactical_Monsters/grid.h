#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include "utils/fileparser.h"
#include "tile.h"

class Grid {
public:
    Grid(QGraphicsScene* scene);
    void loadMap(const QString& path);

    Tile* getTile(int row, int col);

private:
    QGraphicsScene* m_scene;
    std::vector<std::vector<Tile*>> m_tiles;  // store tiles
    void linkNeighbors();
};


#endif // GRID_H
