// Finds memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
/*
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
*/

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
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
/*
    // Detects memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
*/

    // Random seed
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinder");

    float size = 10;
    float xOffset = 10;
    float yOffset = 10;

    Grid *grid1 = new Grid(40, 40);
    MazeGenerator mazeGenerator = MazeGenerator(grid1);
    PathFinder pathFinder = PathFinder(grid1);

    //mazeGenerator.generateAnimated(&window, 50, size, xOffset, yOffset);
    while (window.isOpen()) {
        sf::Event event;

        window.clear();

        // generate maze if has not generated
        if (!mazeGenerator.isGenerationFinished()) {
            mazeGenerator.generateAnimatedStep(&window, size, xOffset, yOffset);
            sf::sleep(sf::milliseconds(1));
        } else { // otherwise find the path
            pathFinder.dijkstraPathAnimatedStep(&window, size, xOffset, yOffset);
            sf::sleep(sf::milliseconds(1));
        }
        

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
                    // Resets the pathfinder so that it must search again
                    pathFinder.reset();
                }
                
            }
        }

        window.display();
    }

    delete grid1;
    return 0;
}
