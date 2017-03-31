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

sf::RectangleShape tileToRect(Tile &tile, float size, float xPos, float yPos, float xOffset = 0, float yOffset = 0, bool isSource = false, bool isDest = false) {
	sf::RectangleShape rect(sf::Vector2f(size, size));

	if(tile.isWall()) rect.setFillColor(sf::Color::Cyan);
	else if(isSource) rect.setFillColor(sf::Color::Yellow);
	else if(isDest) rect.setFillColor(sf::Color::Red);
	else rect.setFillColor(sf::Color::White);

	rect.setPosition(sf::Vector2f(xOffset + xPos * size, yOffset + yPos * size));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	return rect;
}

void drawGrid(sf::RenderWindow &window, Grid *graph, int size = 5, int xOffset = 10, int yOffset = 10) {
	for(int y = 0; y < graph->getHeight(); ++y) {
		for(int x = 0; x < graph->getWidth(); ++x) {
			Tile &tile = graph->getTileAt(x, y);
			window.draw(tileToRect(tile, size, x, y, xOffset, yOffset, graph->isSource(x, y), graph->isDest(x, y)));
		}
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
		window.display();
	}
	delete graph1;
	delete graph2;
	return 0;
}