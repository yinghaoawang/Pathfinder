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
#include "Tile.h"
#include "Grid.h"

// Returns a representation of a grid as Rectangle Shapes
std::vector<sf::RectangleShape> gridToRects(Grid *grid, int size = 5, int xOffset = 10, int yOffset = 10) {
    std::vector<sf::RectangleShape> rects;
    for (int y = 0; y < grid->getHeight(); ++y) {
        for (int x = 0; x < grid->getWidth(); ++x) {
            sf::RectangleShape rect(sf::Vector2f(size, size));

            Tile &tile = grid->getTileAt(x, y);
            if (tile.isWall()) rect.setFillColor(sf::Color(30, 30, 30));
            else if (grid->isSource(x, y)) rect.setFillColor(sf::Color::Yellow);
            else if (grid->isDest(x, y)) rect.setFillColor(sf::Color::Red);
            else rect.setFillColor(sf::Color::White);

            rect.setPosition(sf::Vector2f(xOffset + x * size, yOffset + y * size));
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color::Black);

            rects.push_back(rect);
        }
    }
    return rects;
}

// Given a list of Rectangle Shapes, they are drawn on the window
void drawRects(sf::RenderWindow &window, std::vector<sf::RectangleShape> &rects) {
    for (auto it = rects.begin(), end = rects.end(); it != end; ++it) {
        window.draw(*it);
    }
}

// A list of pairs to a list of Rectangle Shapes
std::vector<sf::RectangleShape> pairsToRects(std::vector<std::pair<int, int>> &pairList, int size = 5, int xOffset = 10, int yOffset = 10) {
    std::vector < sf::RectangleShape> rects;
    for (auto it = pairList.begin(), end = pairList.end(); it != end; ++it) {
        sf::RectangleShape rect(sf::Vector2f(size, size));
        std::pair<int, int> coords = *it;
        rect.setFillColor(sf::Color::Blue);

        rect.setPosition(sf::Vector2f(xOffset + coords.first * size, yOffset + coords.second * size));
        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color::Black);
        rects.push_back(rect);
    }
    return rects;
}

int main() {
    // Detects memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Random seed
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinder");
    /*
    Grid *graph1 = new Grid(std::string(
        "##      ###  ## #  ###      #D\n"
        "#  #               ##  #  # # \n"
        "#  ## ### ### # ###           \n"
        "S    #########       #    #  #\n"
    ));
    */


    Grid *grid1 = new Grid(20, 20);
    grid1->generateMaze();

    std::vector<std::pair<int, int>> path2 = grid1->findPathWithDijkstra();

    while (window.isOpen()) {
        sf::Event event;


        window.clear();

        float size = 10;
        float xOffset = 10;
        float yOffset = 10;

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
                    path2 = grid1->findPathWithDijkstra();
                }
            }
        }

        window.display();
    }
    delete grid1;
    std::cout << "done" << std::endl;
    return 0;
}