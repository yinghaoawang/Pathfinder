#include "Grid.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

// inf uses a sentinel value, do not like, maybe change?
#define INF 999999999 // infinity
#define UNDEF -1 // undefined

Grid::Grid(int w, int h) : width(w), height(h) {
    width = w;
    height = h;
    source = std::make_pair(UNDEF, UNDEF);
    dest = std::make_pair(UNDEF, UNDEF);
    // Instantiate empty tiles with ascending values according to their x and yumns (see below comments)
    tiles = new Tile*[height];
    for (int y = 0; y < height; ++y) {
        tiles[y] = new Tile[width];
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // i.e Value of a 3x3 map i (from bottom to top) 0 1 2, 3 4 5, 6 7 8
            tiles[y][x].setValue(height * y + x);
        }
    }
}

// Get adjacent tiles given coordinate of tile
std::vector<std::pair<int, int>> Grid::getNeighbors(int xPos, int yPos) {
    std::vector<std::pair<int, int>> result;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (std::abs(x) == std::abs(y)) continue; // diagonal are not neighbors
            if (x + xPos < 0 || y + yPos < 0 || x + xPos >= width || y + yPos >= height) continue; // must be in bounds
            if (getTileAt(x + xPos, y + yPos).isWall()) continue; // ignores walls
            result.push_back(std::make_pair(x + xPos, y + yPos));
        }
    }
    return result;
}
std::vector<std::pair<int, int>> Grid::getNeighbors(std::pair<int, int> vertex) {
    return getNeighbors(vertex.first, vertex.second);
}

// Get adjacent tiles that are 2 tiles away, does not matter if they're walls
std::vector<std::pair<int, int>> Grid::getMazeNeighbors(int xPos, int yPos, bool **visited) {
    std::vector<std::pair<int, int>> result;
    for (int x = -2; x <= 2; x += 2) {
        for (int y = -2; y <= 2; y += 2) {
            if (std::abs(x) == std::abs(y)) continue;
            if (x + xPos < 0 || y + yPos < 0 || x + xPos >= width || y + yPos >= height) continue;
            if (visited[y + yPos][x + xPos] == true) continue;
            result.push_back(std::make_pair(x + xPos, y + yPos));
        }
    }
    return result;
}
std::vector<std::pair<int, int>> Grid::getMazeNeighbors(std::pair<int, int> vertex, bool **visited) {
    return getMazeNeighbors(vertex.first, vertex.second, visited);
}

void printListOfPairs(std::vector<std::pair<int, int>> vector) {
    for (auto it = vector.begin(), end = vector.end(); it != end; ++it) {
        //std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    //std::cout << std::endl;
}

// Generate a maze using prim's algorithm
void Grid::generateMaze() {
    bool **visited = new bool*[height];

    // fill the grid up with walls
    for (int y = 0; y < height; ++y) {
        visited[y] = new bool[width];
        for (int x = 0; x < width; ++x) {
            tiles[y][x].setWall(true);
            visited[y][x] = false;
        }
    }

    // prim's algorithm
    std::vector<std::pair<int, int>> cells;
    // choose a random cell, mark it as visited, and add it to the vector
    //std::pair<int, int> cell = std::make_pair(rand() % width, rand() % height);
    std::pair<int, int> cell = std::make_pair(0, 0);
    visited[cell.second][cell.first] = true;
    cells.push_back(cell);
    
    // while there are cells on the vector
    while (!cells.empty()) {
        //std::cout << cells.size() << std::endl;
        //printListOfPairs(cells);
        // pick a cell off the vector
        cell = cells.back();
        cells.pop_back();
        // add its neighbors to the vector
        std::vector<std::pair<int, int>> neighbors = getMazeNeighbors(cell, visited);
        cells.insert(cells.end(), neighbors.begin(), neighbors.end());
        std::unique(cells.begin(), cells.end()); // removes duplicates
        // knock down a wall between it and a neighbor
        std::random_shuffle(neighbors.begin(), neighbors.end()); // randomize the neighbors array
        for (auto it = neighbors.begin(), end = neighbors.end(); it != end; ++it) {
            int x = cell.first;
            int y = cell.second;
            int neighX = it->first;
            int neighY = it->second;
            /*
            std::cout << "cell: " << x << " " << y << std::endl;
            std::cout << "neigh: " << neighX << " " << neighY << std::endl;
            std::cout << "between: " << ((x + neighX) / 2)<< " " << ((y + neighY) / 2) << std::endl;
            */
            Tile &tileInBetween = getTileAt(((x + neighX) / 2), ((y + neighY) / 2));
            if (tileInBetween.isWall()) {
                tileInBetween.setWall(false);
                //std::cout << "visited[" << y << "][" << x << "]" << std::endl;
                break;
            }
        }
        // mark that cell visited
        getTileAt(cell.first, cell.second).setWall(false);
        visited[cell.second][cell.first] = true;
    }
    setSource(0, 0);
    int destX = width - 1;
    int destY = height - 1;
    if (width % 2 == 0) --destX;
    if (height % 2 == 0) --destY;
    setDest(destX, destY);
    //std::cout << "dest: " << dest.first << " " << dest.second << std::endl;

    // free
    for (int y = 0; y < height; ++y) {
        delete[] visited[y];
    }
    delete visited;
}

// Returns a vector of coordinates of the shortest path from source to dest using Dijkstra's algorithm
std::vector<std::pair<int, int>> Grid::findPathWithDijkstra() {
    std::vector<std::pair<int, int>> result;

    // if source and/or dest is not defined then no path exists
    if (source.first == UNDEF || source.second == UNDEF) {
        std::cout << "Source not defined, no path exists" << std::endl;
        return result;
    }
    if (dest.first == UNDEF || dest.second == UNDEF) {
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
            dist[y][x] = INF;
            parent[y][x] = std::make_pair(UNDEF, UNDEF);
            unvisited.push_back(std::make_pair(x, y));
        }
    }

    dist[source.second][source.first] = 0; // dist from source to source
    //std::cout << unvisited.size() << std::endl;

    //std::cout << "Src: " << source.first << ", " << source.second << std::endl;
    //std::cout << "Dest: " << dest.first << ", " << dest.second << std::endl;

    while (!unvisited.empty()) {
        std::pair<int, int> u = getMinVertex(unvisited, dist);
        if (u.first == UNDEF || u.second == UNDEF) break;
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

        //std::cout << unvisited.size() << std::endl;
        //std::cout << "(" << u.first << ", " << u.second << "): " << dist[u.second][u.first] << std::endl;
        std::vector<std::pair<int, int>> neighbors = getNeighbors(u);
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
    if (dist[dest.second][dest.first] != INF) {
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


// Gets the minimum distance from a vector of vertices
std::pair<int, int> Grid::getMinVertex(std::vector<std::pair<int, int>> &vertices, int **dist) {
    int minDist = INF;
    std::pair<int, int> minPair = std::make_pair(UNDEF, UNDEF);
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

bool Grid::isSource(int x, int y) {
    return source.first == x && source.second == y;
}

bool Grid::isDest(int x, int y) {
    return dest.first == x && dest.second == y;
}

void Grid::setSource(int x, int y) { source = std::make_pair(x, y); }

void Grid::setDest(int x, int y) { dest = std::make_pair(x, y); }

// Parses a string # is a wall
Grid::Grid(std::string strMap) {
    // Determine the size of the graph by the size of the string delimited by \n
    height = std::count(strMap.begin(), strMap.end(), '\n');
    if (height != 0) {
        std::string firstRow = strMap.substr(0, strMap.find('\n'));
        width = firstRow.size();
    } else {
        width = 0;
    }

    // Instantiate blank tiles
    tiles = new Tile*[height];
    for (int i = 0; i < height; ++i) {
        tiles[i] = new Tile[width];
    }

    // Gets each row as strings delimited by newspace
    int prevFoundIndex = 0;
    for (int y = 0; y < height; ++y) {
        std::string line = strMap.substr(prevFoundIndex, strMap.find('\n', prevFoundIndex));
        prevFoundIndex = strMap.find('\n', prevFoundIndex) + 1;
        for (int x = 0; x < width; ++x) {
            Tile &tile = tiles[y][x];
            tile.setValue(height * y + x);

            // Determines what tile it is with asciis
            if (line[x] == '#') tile.setWall(true);
            else if (line[x] == 'S') setSource(x, y);
            else if (line[x] == 'D') setDest(x, y);
        }
    }

}

Grid::~Grid() {
    for (int y = 0; y < height; ++y) {
        delete[] tiles[y];
    }

    delete tiles;
}

int Grid::getWidth() {
    return width;
}

int Grid::getHeight() {
    return height;
}

Tile &Grid::getTileAt(int x, int y) {
    return tiles[y][x];
}

void Grid::randomizeTiles() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile &tile = tiles[y][x];
            if (isSource(x, y) || isDest(x, y)) continue;
            if (rand() % 2 == 0) {
                tile.setWall(true);
            }
        }
    }
}

// Prints out the graph where # is a wall and ` is empty
std::ostream & operator<<(std::ostream &os, Grid &g) {
    for (int y = 0; y < g.getHeight(); ++y) {
        for (int x = 0; x < g.getWidth(); ++x) {
            Tile tile = g.getTileAt(x, y);
            // os << tile;
            char c = tile.isWall() ? '#' : '`';
            if (g.isSource(x, y)) c = 'S';
            else if (g.isDest(x, y)) c = 'D';
            os << c;
        }
        os << "\n";
    }
    return os;
}
