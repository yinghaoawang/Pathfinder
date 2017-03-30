#pragma once
#include <list>
#include <ostream>
#include "Tile.h"

class Graph {
private:
	int rows, cols;
	int source[2];
	int dest[2];
	Tile **adj;
public:
	void init();
	Graph(int r, int c);
	bool isSource(int row, int col);
	bool isDest(int row, int col);
	Graph(std::string strMap);
	int getRows();
	int getCols();
	Tile getTileAt(int r, int c);

	void randomizeTiles();
	friend std::ostream& operator<<(std::ostream &os, Graph &g);
};

