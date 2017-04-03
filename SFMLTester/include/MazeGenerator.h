#pragma once
#include "Grid.h"

class MazeGenerator {
private:
    Grid *grid;
    bool **visited;
    std::vector<std::pair<int, int>> frontier;
    bool generationFinished;
    
    std::vector<std::pair<int, int>> getMazeNeighbors(int xPos, int yPos);
    std::vector<std::pair<int, int>> getMazeNeighbors(std::pair<int, int> vertex);
public:
    MazeGenerator(Grid *g);
    ~MazeGenerator();

    bool isGenerationFinished();

    void generateAnimatedStep(sf::RenderWindow * window, int size, int xOffset, int yOffset);
    void generate();
};