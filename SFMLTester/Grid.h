#pragma once
#include <list>
#include <ostream>
#include "Tile.h"

class Grid {
private:
	int width, height;
	// index 0 is x, index 1 is y
	std::pair<int, int> source;
	std::pair<int, int> dest;
	// Note that tiles is not a 2d array of dynamically allocated tiles, but a 1d array of an array of tiles
	Tile **tiles;
public:
	Grid(int width, int height);
	std::list<Tile*> getNeighbors(int x, int y);
	std::list<std::pair<int, int>> findPathWithDijkstra();
	Grid(std::string strMap);
	~Grid();

	bool isSource(int x, int y);
	bool isDest(int x, int y);
	void setSource(int x, int y);
	void setDest(int x, int y);
	int getWidth();
	int getHeight();
	Tile &getTileAt(int x, int y);

	void randomizeTiles();
	friend std::ostream& operator<<(std::ostream &os, Grid &g);
};

