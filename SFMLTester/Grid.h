#pragma once
#include <vector>
#include <ostream>
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Grid {
private:
    int width, height;
    // index 0 is x, index 1 is y
    std::pair<int, int> source;
    std::pair<int, int> dest;
    // Note that tiles is not a 2d array of dynamically allocated tiles, but a 1d array of an array of tiles
    // These are also the vertices
    Tile **tiles;
    std::pair<int, int> getMinVertex(std::vector<std::pair<int, int>>& vector, int ** dist);

public:
    Grid(int width, int height);
    std::vector<std::pair<int, int>> getNeighbors(int x, int y);
    std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> vertex);
    std::vector<std::pair<int, int>> getMazeNeighbors(int xPos, int yPos);
    std::vector<std::pair<int, int>> getMazeNeighbors(std::pair<int, int> vertex);
    void generateMazeAnimated(sf::RenderWindow * window, int msDelay, int size, int xOffset, int yOffset);
    //std::vector<std::pair<int, int>> getMazeNeighbors(int xPos, int yPos);
    //std::vector<std::pair<int, int>> getMazeNeighbors(std::pair<int, int> vertex);
    void generateMaze();
    void generateMazeAnimated(sf::RenderWindow & window, int delay, int size, int xOffset, int yOffset);
    std::vector<std::pair<int, int>> findPathWithDijkstra();
    Grid(std::string strMap);
    ~Grid();



    bool isSource(int x, int y);
    bool isDest(int x, int y);
    void setSource(int x, int y);
    void setDest(int x, int y);
    int getWidth();
    int getHeight();
    Tile &getTileAt(int x, int y);

    void randomizeTiles();
    friend std::ostream& operator<<(std::ostream &os, Grid &g);
};

