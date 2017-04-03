#pragma once
#include "Grid.h"
// Returns a vector of coordinates of the shortest path from source to dest using Dijkstra's algorithm
class PathFinder {
private:
    Grid *grid;
    bool pathFound;

    int **dist;
    std::pair<int, int> **parent;
    std::vector<std::pair<int, int>> unvisited;
    std::pair<int, int> getMinVertex(std::vector<std::pair<int, int>>& vector, int ** dist);

public:
    PathFinder(Grid * g);
    ~PathFinder();

    void reset();

    void dijkstraPathAnimatedStep(sf::RenderWindow * window, int size, int xOffset, int yOffset);
};