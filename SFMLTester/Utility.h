#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <vector>

std::vector<sf::RectangleShape> gridToRects(Grid *grid, int size = 5, int xOffset = 10, int yOffset = 10);
void drawRects(sf::RenderWindow &window, std::vector<sf::RectangleShape> &rects);
std::vector<sf::RectangleShape> pairsToRects(std::vector<std::pair<int, int>> &pairList, int size = 5, int xOffset = 10, int yOffset = 10);

