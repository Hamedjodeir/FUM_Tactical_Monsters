#include "grid.h"
#include "tile.h"
#include <QDebug>

Grid::Grid(QGraphicsScene* scene) : m_scene(scene) {}

void Grid::loadMap(const QString& path) {
    FileParser parser;
    QVector<QStringList> gridText = parser.parseMap(path);

    for (int row = 0; row < gridText.size(); ++row) {
        const QStringList& line = gridText[row];
        for (int col = 0; col < line.size(); ++col) {
            QString token = line[col].trimmed();
            TileType type = Empty;

            if (token.contains("1")) type = Grass;
            else if (token.contains("~")) type = Water;
            else if (token.contains("#")) type = Obstacle;
            else if (token.contains("2")) type = Lava;

            Tile* tile = new Tile(type, row, col);
            m_scene->addItem(tile);
        }
    }

    QRectF bounds = m_scene->itemsBoundingRect();
    m_scene->setSceneRect(bounds.center().x() - 700, bounds.center().y() - 350, 1400, 700);
}
