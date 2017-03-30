#pragma once
#include <list>
#include <ostream>
#include "Tile.h"

class Graph {
private:
	int rows, cols;
	Tile **adj;
public:
	Graph(int r, int c);
	int getRows();
	int getCols();
	Tile getTileAt(int r, int c);

	void randomizeTiles();
	friend std::ostream& operator<<(std::ostream &os, Graph &g);
};

