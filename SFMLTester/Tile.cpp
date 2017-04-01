#include "Tile.h"
#include <iostream>

bool Tile::isWall() {
    return wall;
}

int Tile::getValue() {
    return value;
}

void Tile::setWall(bool w) {
    wall = w;
}

void Tile::setValue(int v) {
    value = v;
}

Tile::Tile() {
    wall = false;
    value = 1;
}

Tile::Tile(bool w = false, int v = 1) : wall(w), value(v) {}
Tile::~Tile() {}

std::ostream & operator<<(std::ostream & os, Tile & t) {
    os << t.getValue();
    return os;
}
