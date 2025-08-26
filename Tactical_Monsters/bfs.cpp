#include "bfs.h"

std::vector<Tile*> BFS::search(Tile* start, int mobility) {
    std::vector<Tile*> reachable;
    if (!start) return reachable;

    std::queue<std::pair<Tile*, int>> q;
    std::unordered_map<Tile*, bool> visited;

    q.push({start, 0});
    visited[start] = true;

    while (!q.empty()) {
        auto [tile, dist] = q.front();
        q.pop();

        if (dist > mobility) continue;

        reachable.push_back(tile);

        for (Tile* neighbor : tile->neighbors()) {
            if (!visited[neighbor]) {
                // Example rule: cannot walk on obstacle/lava
                if (neighbor->type() == Obstacle || neighbor->type() == Lava) continue;

                visited[neighbor] = true;
                q.push({neighbor, dist+1});
            }
        }
    }

    return reachable;
}
