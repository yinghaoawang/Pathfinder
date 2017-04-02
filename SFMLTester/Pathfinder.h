#pragma once
#include "Grid.h"
// Returns a vector of coordinates of the shortest path from source to dest using Dijkstra's algorithm
class PathFinder {
private:
    std::pair<int, int> getMinVertex(std::vector<std::pair<int, int>>& vector, int ** dist);

public:
    std::vector<std::pair<int, int>> PathFinder::findPathWithDijkstra(Grid &grid);
};