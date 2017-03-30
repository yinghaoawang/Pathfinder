#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "Tile.h"
#include "Graph.h"

sf::RectangleShape tileToRect(Tile tile, int size, float xPos, float yPos) {
	sf::RectangleShape rect(sf::Vector2f(size, size));

	if(tile.isWall()) rect.setFillColor(sf::Color::Cyan);
	rect.setPosition(sf::Vector2f(xPos * size, yPos * size));
	return rect;
}

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Graph *graph = new Graph(3, 3);

	graph->randomizeTiles();
	std::cout << *graph << std::endl;
	graph->randomizeTiles();
	std::cout << *graph << std::endl;
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		int size = 100;
		for(int i = 0; i < graph->getRows(); ++i) {
			for(int j = 0; j < graph->getCols(); ++j) {
				Tile &tile = graph->getTileAt(i, j);
				int xPos = j;
				int yPos = graph->getCols() - 1 - i;
				window.draw(tileToRect(tile, size, xPos, yPos));
			}
		}
		window.display();
	}

	return 0;
}