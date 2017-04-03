#include "PathFinder.h"
#include "Utility.h"
#include <iostream>

// Constructor
PathFinder::PathFinder(Grid *g) {
    grid = g;
    pathFound = false;

    dist = new int*[g->getHeight()];
    parent = new std::pair<int, int>*[g->getHeight()];

    // initialization
    for (int y = 0; y < g->getHeight(); ++y) {
        dist[y] = new int[g->getWidth()];
        parent[y] = new std::pair<int, int>[g->getWidth()];
        for (int x = 0; x < g->getWidth(); ++x) {
            dist[y][x] = Grid::INF;
            parent[y][x] = std::make_pair(Grid::UNDEF, Grid::UNDEF);
            unvisited.push_back(std::make_pair(x, y));
        }
    }
    
}

// Destructor
PathFinder::~PathFinder() {
    // free
    for (int y = 0; y < grid->getHeight(); ++y) {
        delete[] parent[y];
        delete[] dist[y];
    }
    delete parent;
    delete dist;
}

void PathFinder::reset() {
    pathFound = false;
    for (int y = 0; y < grid->getHeight(); ++y) {
        for (int x = 0; x < grid->getWidth(); ++x) {
            dist[y][x] = Grid::INF;
            parent[y][x] = std::make_pair(Grid::UNDEF, Grid::UNDEF);
            unvisited.push_back(std::make_pair(x, y));
        }
    }
}

// Gets the minimum distance from a vector of vertices
std::pair<int, int> PathFinder::getMinVertex(std::vector<std::pair<int, int>> &vertices, int **dist) {
    int minDist = Grid::INF;
    std::pair<int, int> minPair = std::make_pair(Grid::UNDEF, Grid::UNDEF);
    // iterate through the vector
    for (auto it = vertices.begin(), end = vertices.end(); it != end; ++it) {
        std::pair<int, int> currPair = *it;
        int currDist = dist[currPair.second][currPair.first];
        // if minimum distance is not set or current distance is less than minimum, then set this distance to minimum distance
        if (currDist < minDist) {
            minDist = currDist;
            minPair = currPair;
        }
    }
    // does not check if min pair is still undefined
    return minPair;
}

// Returns a vector of coordinates of the shortest path from source to dest using Dijkstra's algorithm
void PathFinder::dijkstraPathAnimatedStep(sf::RenderWindow *window, int size, int xOffset, int yOffset) {
    std::pair<int, int> source = grid->getSource();
    std::pair<int, int> dest = grid->getDest();

    dist[grid->getSource().second][grid->getSource().first] = 0; // dist from source to source

    // if source and/or dest is not defined then no path exists
    if (source.first == Grid::UNDEF || source.second == Grid::UNDEF) {
        std::cout << "Source not defined, no path exists" << std::endl;
        return;
    }
    if (dest.first == Grid::UNDEF || dest.second == Grid::UNDEF) {
        std::cout << "Dest is not defined, no path exists" << std::endl;
        return;
    }

    // draw grid
    std::vector<sf::RectangleShape> tiles = gridToRects(grid, size, xOffset, yOffset);
    drawRects(*window, tiles);

    // if path is found then draw path
    if (pathFound) {
        // put the path in a vector
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> vertex = parent[dest.second][dest.first];
        while (vertex != source) {
            //std::cout << vertex.first << " " << vertex.second << std::endl;
            path.push_back(vertex);
            vertex = parent[vertex.second][vertex.first];

        }

        // draw path
        std::vector<sf::RectangleShape> pathTiles = pairsToRects(path, size, xOffset, yOffset, sf::Color(0, 0, 120));
        drawRects(*window, pathTiles);
    }

    if (!unvisited.empty()) {
        std::pair<int, int> u = getMinVertex(unvisited, dist);
        if (u.first != Grid::UNDEF && u.second != Grid::UNDEF) {
            unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

            std::vector<std::pair<int, int>> neighbors = grid->getNeighbors(u);
            for (auto it = neighbors.begin(), end = neighbors.end(); it != end; ++it) {
                std::pair<int, int> v = *it;
                int alt = dist[u.second][u.first] + 1; // length(u, v) is 1
                if (alt < dist[v.second][v.first]) {
                    dist[v.second][v.first] = alt;
                    parent[v.second][v.first] = u;
                }

                if (v.first == dest.first && v.second == dest.second) pathFound = true;
            }

            // black out the unvisited
            std::vector<sf::RectangleShape> unvisitedTiles = pairsToRects(unvisited, size, xOffset, yOffset, sf::Color(30, 30, 30));
            drawRects(*window, unvisitedTiles);
        }
    }

    
}
