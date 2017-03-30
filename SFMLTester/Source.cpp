#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "Tile.h"
#include "Graph.h"

sf::RectangleShape tileToRect(Tile tile, float size, float xPos, float yPos, float xOffset = 0, float yOffset = 0, bool isSource = false, bool isDest = false) {
	sf::RectangleShape rect(sf::Vector2f(size, size));

	if(tile.isWall()) rect.setFillColor(sf::Color::Cyan);
	else if(isSource) rect.setFillColor(sf::Color::Yellow);
	else if(isDest) {
		rect.setFillColor(sf::Color::Red);
		//std::cout << "is dest";
	}
	else rect.setFillColor(sf::Color::White);

	rect.setPosition(sf::Vector2f(xOffset + xPos * size, yOffset + yPos * size));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	return rect;
}

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Graph *graph = new Graph(std::string(
		"##      ###  ## #  ##     D\n"
		"#  #   #               # # \n"
		"#  ## ### ### # ####       \n"
		"S                       # #\n"
	));

	/*
	graph->randomizeTiles();
	std::cout << *graph << std::endl;
	graph->randomizeTiles();
	*/
	std::cout << *graph << std::endl;
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
		for(int i = 0; i < graph->getRows(); ++i) {
			for(int j = 0; j < graph->getCols(); ++j) {
				Tile &tile = graph->getTileAt(i, j);
				int xPos = j;
				int yPos = graph->getCols() - 1 - i;
				bool isDest = graph->isDest(i, j);
				window.draw(tileToRect(tile, size, xPos, yPos, xOffset, yOffset, graph->isSource(i, j), isDest));
			}
		}
		window.display();
	}

	return 0;
}