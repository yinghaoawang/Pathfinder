// Finds memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "Tile.h"
#include "Grid.h"

void drawGrid(sf::RenderWindow &window, Grid *grid, int size = 5, int xOffset = 10, int yOffset = 10) {
	for(int y = 0; y < grid->getHeight(); ++y) {
		for(int x = 0; x < grid->getWidth(); ++x) {
			sf::RectangleShape rect(sf::Vector2f(size, size));
			
			Tile &tile = grid->getTileAt(x, y);
			if(tile.isWall()) rect.setFillColor(sf::Color::Cyan);
			else if(grid->isSource(x, y)) rect.setFillColor(sf::Color::Yellow);
			else if(grid->isDest(x, y)) rect.setFillColor(sf::Color::Red);
			else rect.setFillColor(sf::Color::White);

			rect.setPosition(sf::Vector2f(xOffset + x * size, yOffset + y * size));
			rect.setOutlineThickness(1);
			rect.setOutlineColor(sf::Color::Black);

			window.draw(rect);
		}
	}
}

void drawPath(sf::RenderWindow &window, Grid *grid, std::list<std::pair<int, int>> pathList, int size = 5, int xOffset = 10, int yOffset = 10) {
	for(auto it = pathList.begin(), end = pathList.end(); it != end; ++it) {
		sf::RectangleShape rect(sf::Vector2f(size, size));
		std::pair<int, int> coords = *it;
		rect.setFillColor(sf::Color::Blue);

		rect.setPosition(sf::Vector2f(xOffset + coords.first * size, yOffset + coords.second * size));
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::Black);
		window.draw(rect);
	}
}

int main() {
	// Detects memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Random seed
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Grid *graph1 = new Grid(std::string(
		"##      ###  ## #  ###      #D\n"
		"#  #               ##  #  # # \n"
		"#  ## ### ### # ###           \n"
		"S    #########       #    #  #\n"
	));

	Grid *graph2 = new Grid(4, 2);
	graph2->randomizeTiles();
	std::list<std::pair<int, int>> path = graph1->findPathWithDijkstra();

	/*
	graph->randomizeTiles();
	std::cout << *graph << std::endl;
	graph->randomizeTiles();
	*/

	std::cout << *graph1 << std::endl;
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		float size = 20;
		float xOffset = 10;
		float yOffset = 10;
		drawGrid(window, graph1, size, xOffset, yOffset);
		drawPath(window, graph1, path, size, xOffset, yOffset);
		window.display();
	}
	delete graph1;
	delete graph2;
	return 0;
}