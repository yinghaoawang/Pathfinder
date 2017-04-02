#include "PathFinder.h"
#include <iostream>

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
std::vector<std::pair<int, int>> PathFinder::findPathWithDijkstra(Grid &grid) {
    std::vector<std::pair<int, int>> result;

    std::pair<int, int> source = grid.getSource();
    std::pair<int, int> dest = grid.getDest();
    int height = grid.getHeight();
    int width = grid.getWidth();

    // if source and/or dest is not defined then no path exists
    if (source.first == Grid::UNDEF || source.second == Grid::UNDEF) {
        std::cout << "Source not defined, no path exists" << std::endl;
        return result;
    }
    if (dest.first == Grid::UNDEF || dest.second == Grid::UNDEF) {
        std::cout << "Dest is not defined, no path exists" << std::endl;
        return result;
    }

    std::vector<std::pair<int, int>> unvisited;
    int **dist = new int*[height];
    std::pair<int, int> **parent = new std::pair<int, int>*[height];

    // initialization
    for (int y = 0; y < height; ++y) {
        dist[y] = new int[width];
        parent[y] = new std::pair<int, int>[width];
        for (int x = 0; x < width; ++x) {
            dist[y][x] = Grid::INF;
            parent[y][x] = std::make_pair(Grid::UNDEF, Grid::UNDEF);
            unvisited.push_back(std::make_pair(x, y));
        }
    }

    dist[source.second][source.first] = 0; // dist from source to source

    while (!unvisited.empty()) {
        std::pair<int, int> u = getMinVertex(unvisited, dist);
        if (u.first == Grid::UNDEF || u.second == Grid::UNDEF) break;
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

        //std::cout << unvisited.size() << std::endl;
        //std::cout << "(" << u.first << ", " << u.second << "): " << dist[u.second][u.first] << std::endl;
        std::vector<std::pair<int, int>> neighbors = grid.getNeighbors(u);
        for (auto it = neighbors.begin(), end = neighbors.end(); it != end; ++it) {
            std::pair<int, int> v = *it;
            int alt = dist[u.second][u.first] + 1; // length(u, v) is 1
            if (alt < dist[v.second][v.first]) {
                dist[v.second][v.first] = alt;
                parent[v.second][v.first] = u;
            }
        }
        //std::cout << "(" << u.first << ", " << u.second << "): " << dist[u.second][u.first] << "- parent: " << parent[u.second][u.first].first << ", " << parent[u.second][u.first].second << std::endl;

    }

    // if found a path then put it into the vector
    if (dist[dest.second][dest.first] != Grid::INF) {
        std::pair<int, int> vertex = parent[dest.second][dest.first];
        while (vertex != source) {
            //std::cout << vertex.first << " " << vertex.second << std::endl;
            result.push_back(vertex);
            vertex = parent[vertex.second][vertex.first];

        }
    }

    // free
    for (int y = 0; y < height; ++y) {
        delete[] parent[y];
        delete[] dist[y];
    }
    delete parent;
    delete dist;

    return result;
}
