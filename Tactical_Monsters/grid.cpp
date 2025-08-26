#include "grid.h"
#include "tile.h"
#include <QDebug>
#include "parser.h"

Grid::Grid(QGraphicsScene* scene) : m_scene(scene) {}

void Grid::loadMap(const QString& path) {
    Parser parser(1); // or based on path
    auto parsed = parser.parse();

    int rows = 5;
    int cols = 9;
    m_tiles.resize(rows, std::vector<Tile*>(cols, nullptr));

    for (auto& [x, y, z, _, __] : parsed) {
        TileType type = Empty;
        if (z == '1') type = Grass;
        else if (z == '~') type = Water;
        else if (z == '#') type = Obstacle;
        else if (z == '2') type = Lava;

        Tile* tile = new Tile(type, x, y);
        m_scene->addItem(tile);
        m_tiles[x][y] = tile;
    }

    linkNeighbors();

    QRectF bounds = m_scene->itemsBoundingRect();
    m_scene->setSceneRect(bounds.center().x() - 700, bounds.center().y() - 350, 1400, 700);
}

Tile* Grid::getTile(int row, int col) {
    if (row < 0 || row >= (int)m_tiles.size()) return nullptr;
    if (col < 0 || col >= (int)m_tiles[row].size()) return nullptr;
    return m_tiles[row][col];
}

void Grid::linkNeighbors() {
    int rows = m_tiles.size();
    int cols = m_tiles[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Tile* tile = m_tiles[r][c];
            if (!tile) continue;

            std::vector<std::pair<int,int>> directions;
            if (c % 2 == 0) {
                directions = {{-1,0}, {-1,-1}, {0,-1}, {1,0}, {0,1}, {-1,1}};
            } else {
                directions = {{-1,0}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}};
            }

            for (auto [dr, dc] : directions) {
                Tile* neighbor = getTile(r+dr, c+dc);
                if (neighbor) {
                    tile->addNeighbor(neighbor);
                }
            }
        }
    }
}

