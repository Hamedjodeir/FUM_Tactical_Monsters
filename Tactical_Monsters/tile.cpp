#include "tile.h"
#include <QPolygonF>
#include <QtMath>

Tile::Tile(TileType type, int row, int col) {
    const int size = 30; // radius of hex
    QPolygonF hex;
    for (int i = 0; i < 6; ++i) {
        qreal angle_deg = 60 * i;  // flat-topped
        qreal angle_rad = M_PI / 180 * angle_deg;
        hex << QPointF(size * cos(angle_rad), size * sin(angle_rad));
    }
    setPolygon(hex);

    // Hex geometry for flat-topped layout
    qreal width = 2 * size;
    qreal height = sqrt(3) * size;
    qreal xOffset = col * (3.0 / 4.0 * width);
    qreal yOffset = row * height;

    if (col % 2 == 1) {
        yOffset += height / 2.0; // stagger odd columns
    }

    setPos(xOffset, yOffset);
    setStyle(type);
}

void Tile::setStyle(TileType type) {
    switch (type) {
    case Grass:    setBrush(QBrush(Qt::green)); break;
    case Water:    setBrush(QBrush(Qt::blue));  break;
    case Obstacle: setBrush(QBrush(Qt::gray));  break;
    case Lava:     setBrush(QBrush(Qt::red));   break;
    case Empty:
    default:       setBrush(QBrush(Qt::lightGray)); break;
    }
    setPen(QPen(Qt::black));
}
