#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <vector>

std::vector<sf::RectangleShape> gridToRects(Grid *grid, int size = 5, int xOffset = 10, int yOffset = 10, sf::Color wallColor = sf::Color(30, 30, 30), sf::Color sourceColor = sf::Color (40, 100, 40), sf::Color destColor = sf::Color (120, 20, 20));
void drawRects(sf::RenderWindow &window, std::vector<sf::RectangleShape> &rects);
std::vector<sf::RectangleShape> pairsToRects(std::vector<std::pair<int, int>> &pairList, int size = 5, int xOffset = 10, int yOffset = 10, sf::Color color = sf::Color(20, 20, 140));

