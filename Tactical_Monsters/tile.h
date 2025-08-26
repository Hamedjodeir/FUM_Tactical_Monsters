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

// tile.h
class Tile : public QGraphicsPolygonItem {
public:
    Tile(TileType type, int row, int col);

    void setStyle(TileType type);

    int row() const { return m_row; }
    int col() const { return m_col; }

    void addNeighbor(Tile* neighbor);
    const std::vector<Tile*>& neighbors() const { return m_neighbors; }

    TileType tileType() const { return m_type; }

private:
    int m_row;
    int m_col;
    TileType m_type;
    std::vector<Tile*> m_neighbors;
};


#endif // TILE_H
