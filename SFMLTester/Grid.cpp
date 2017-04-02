#include "Grid.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include "Utility.h"

// Constructor takes in width and height of grid
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

// Constructor where it parses a string, # is a wall, all else is empty passage
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

// Destructor
Grid::~Grid() {
    for (int y = 0; y < height; ++y) {
        delete[] tiles[y];
    }

    delete tiles;
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

// Mutators
bool Grid::isSource(int x, int y) { return source.first == x && source.second == y; }
bool Grid::isDest(int x, int y) { return dest.first == x && dest.second == y; }
std::pair<int, int> Grid::getSource() { return source; }
std::pair<int, int> Grid::getDest() { return dest; }
int Grid::getWidth() { return width; }
int Grid::getHeight() {return height; }
Tile &Grid::getTileAt(int x, int y) {return tiles[y][x]; }
void Grid::setSource(int x, int y) { source = std::make_pair(x, y); }
void Grid::setDest(int x, int y) { dest = std::make_pair(x, y); }


// Randomizes tiles, does not create source or account for passages. Completely random.
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
