#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ostream>
#include "Tile.h"

class Grid {
private:
    int width, height;
    // index 0 is x, index 1 is y
    std::pair<int, int> source;
    std::pair<int, int> dest;
    // Note that tiles is not a 2d array of dynamically allocated tiles, but a 1d array of an array of tiles
    // These are also the vertices
    Tile **tiles;

public:
    Grid(int width, int height);
    
    // inf uses a sentinel value, do not like, maybe change?
    static const int INF = 999999999; // infinity
    static const int UNDEF = -1; // undefined

    std::vector<std::pair<int, int>> getNeighbors(int x, int y);
    std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> vertex);
    Grid(std::string strMap);
    ~Grid();

    bool isSource(int x, int y);
    bool isDest(int x, int y);
    std::pair<int, int> getSource();
    std::pair<int, int> getDest();

    void setSource(int x, int y);
    void setDest(int x, int y);
    int getWidth();
    int getHeight();
    Tile &getTileAt(int x, int y);

    void randomizeTiles();
    friend std::ostream& operator<<(std::ostream &os, Grid &g);
};