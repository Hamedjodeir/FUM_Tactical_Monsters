#ifndef BFS_H
#define BFS_H

#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include "tile.h"

class BFS {
public:
    static std::vector<Tile*> search(Tile* start, int mobility);
};


#endif // BFS_H
