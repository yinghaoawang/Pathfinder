#include "Utility.h"
#include <vector>
#include "Grid.h"

// Returns a representation of a grid as Rectangle Shapes
std::vector<sf::RectangleShape> gridToRects(Grid *grid, int size, int xOffset, int yOffset) {
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
            //rect.setOutlineThickness(1);
            //rect.setOutlineColor(sf::Color::Black);

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
std::vector<sf::RectangleShape> pairsToRects(std::vector<std::pair<int, int>> &pairList, int size, int xOffset, int yOffset) {
    std::vector < sf::RectangleShape> rects;
    for (auto it = pairList.begin(), end = pairList.end(); it != end; ++it) {
        sf::RectangleShape rect(sf::Vector2f(size, size));
        std::pair<int, int> coords = *it;
        rect.setFillColor(sf::Color::Blue);

        rect.setPosition(sf::Vector2f(xOffset + coords.first * size, yOffset + coords.second * size));
        //rect.setOutlineThickness(1);
        //rect.setOutlineColor(sf::Color::Black);
        rects.push_back(rect);
    }
    return rects;
}