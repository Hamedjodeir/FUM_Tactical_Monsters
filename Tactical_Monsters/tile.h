#ifndef TILE_H
#define TILE_H

#include <QGraphicsPolygonItem>
#include <QBrush>
#include <QPen>

enum TileType {
    Grass,
    Water,
    Obstacle,
    Lava,
    Empty
};

class Tile : public QGraphicsPolygonItem {
public:
    Tile(TileType type, int row, int col);

private:
    void setStyle(TileType type);
};

#endif // TILE_H
