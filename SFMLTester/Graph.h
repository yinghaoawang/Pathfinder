#pragma once
#include <list>
#include <ostream>
#include "Tile.h"

class Graph {
private:
	int width, height;
	// index 0 is x, index 1 is y
	int source[2];
	int dest[2];
	Tile **adj;
public:
	void init();
	Graph(int width, int height);
	bool isSource(int x, int y);
	bool isDest(int x, int y);
	Graph(std::string strMap);
	int getWidth();
	int getHeight();
	Tile getTileAt(int x, int y);

	void randomizeTiles();
	friend std::ostream& operator<<(std::ostream &os, Graph &g);
};

