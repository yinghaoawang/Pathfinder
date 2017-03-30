#include "Tile.h"
#include <iostream>

bool Tile::isWall() {
	return wall;
}

int Tile::getValue() {
	return value;
}

bool Tile::isVisited() {
	return visited;
}

void Tile::setWall(bool w) {
	wall = w;
}

void Tile::setValue(int v) {
	value = v;
}

void Tile::setVisited(int v) {
	visited = v;
}

Tile::Tile() {
	wall = false;
	value = 1;
	visited = false;
}

Tile::Tile(bool w = false, int v = 1) : wall(w), value(v) {
	visited = false;
}
Tile::~Tile() {}

std::ostream & operator<<(std::ostream & os, Tile & t) {
	os << t.getValue();
	return os;
}
