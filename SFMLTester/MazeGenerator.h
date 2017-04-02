#pragma once
#include "Grid.h"

class MazeGenerator {
private:
    std::vector<std::pair<int, int>> MazeGenerator::getMazeNeighbors(Grid &grid, int xPos, int yPos);
    std::vector<std::pair<int, int>> getMazeNeighbors(Grid & grid, std::pair<int, int> vertex);
    
public:
    void generate(Grid & grid);
    void MazeGenerator::generateAnimated(sf::RenderWindow *window, Grid &grid, int msDelay, int size, int xOffset, int yOffset);
};