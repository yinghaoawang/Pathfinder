// Finds memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "MazeGenerator.h"
#include "PathFinder.h"
#include "Tile.h"
#include "Grid.h"
#include "Utility.h"

int main() {
    // Detects memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Random seed
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinder");

    float size = 10;
    float xOffset = 10;
    float yOffset = 10;

    Grid *grid1 = new Grid(40, 40);
    MazeGenerator().generateAnimated(&window, *grid1, 50, size, xOffset, yOffset);

    std::vector<std::pair<int, int>> path2 = PathFinder().findPathWithDijkstra(*grid1);

    while (window.isOpen()) {
        sf::Event event;
        window.clear();

        std::vector<sf::RectangleShape> tiles = gridToRects(grid1, size, xOffset, yOffset);
        drawRects(window, tiles);

        std::vector<sf::RectangleShape> path = pairsToRects(path2, size, xOffset, yOffset);
        drawRects(window, path);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Mouse position to tile indices
                int xIndex = mousePos.x / size - xOffset / size;
                int yIndex = mousePos.y / size - yOffset / size;
                
                // If within bounds of the grid, toggle the wall status
                if (xIndex >= 0 && yIndex >= 0 && xIndex < grid1->getWidth() && yIndex < grid1->getHeight()) {
                    Tile &tile = grid1->getTileAt(xIndex, yIndex);
                    bool tileIsWall = grid1->getTileAt(xIndex, yIndex).isWall();
                    tile.setWall(!tileIsWall);
                    path2 = PathFinder().findPathWithDijkstra(*grid1);
                }
            }
        }

        window.display();
    }
    delete grid1;
    std::cout << "done" << std::endl;
    return 0;
}