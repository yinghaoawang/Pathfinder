#include "Grid.h"
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <string>

#define INF -1 // infinity
#define UNDEF -2 // undefined

Grid::Grid(int w, int h) : width(w), height(h) {
	width = w;
	height = h;
	// Instantiate empty tiles with ascending values according to their x and yumns (see below comments)
	tiles = new Tile*[height];
	for(int i = 0; i < height; ++i) {
		tiles[i] = new Tile[width];
	}
	for(int x = 0; x < width; ++x) {
		for(int y = 0; y < height; ++y) {
			// i.e Value of a 3x3 map i (from bottom to top) 0 1 2, 3 4 5, 6 7 8
			tiles[y][x].setValue(height * y + x);
		}
	}
}

// Get tilesacent tiles given coordinate of tile
std::list<Tile*> Grid::getNeighbors(int x, int y) {
	std::list<Tile*> result;
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			if(std::abs(x) == std::abs(y)) continue; // diagonal are not neighbors
			if(x < 0 || y < 0 || x >= width || y >= height) continue; // must be in bounds
			result.push_back(&tiles[y][x]);
		}
	}
	return result;
}

// Returns a list of coordinates of the shortest path from source to dest using Dijkstra's algorithm
std::list<std::pair<int, int>> Grid::findPathWithDijkstra() {
	std::list<std::pair<int, int>> result;

	std::list<std::pair<int, int>> unvisited;
	int **dist = new int*[height];
	std::pair<int, int> **parent = new std::pair<int, int>*[height];

	// initialization
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			dist[y][x] = INF;
			parent[y][x] = std::make_pair(UNDEF, UNDEF);
			unvisited.push_back(std::make_pair(x, y));
		}
	}

	// if source and/or dest is not defined then no path exists
	if(source.first == UNDEF || source.second == UNDEF) {
		std::cout << "Source not defined, no path exists" << std::endl;
		return result;
	}
	if(dest.first == UNDEF || dest.second == UNDEF) {
		std::cout << "Dest is not defined, no path exists" << std::endl;
		return result;
	}
	dist[source.second][source.first] = 0; // dist from source to source

	while(!unvisited.empty()) {

	}

	// TODO
	return result;
}

bool Grid::isSource(int x, int y) {
	return source.first == x && source.second == y;
}

bool Grid::isDest(int x, int y) {
	return dest.first == x && dest.second == y;
}

void Grid::setSource(int x, int y) { source = std::make_pair(x, y);  }

void Grid::setDest(int x, int y) { dest = std::make_pair(x, y); }

// Parses a string # is a wall
Grid::Grid(std::string strMap) {
	// Determine the size of the graph by the size of the string delimited by \n
	height = std::count(strMap.begin(), strMap.end(), '\n');
	if(height != 0) {
		std::string firstRow = strMap.substr(0, strMap.find('\n'));
		width = firstRow.size();
	} else {
		width = 0;
	}

	// Instantiate blank tiles
	tiles = new Tile*[height];
	for(int i = 0; i < height; ++i) {
		tiles[i] = new Tile[width];
	}

	// Gets each row as strings delimited by newspace
	int prevFoundIndex = 0;
	for(int y = 0; y < height; ++y) {
		std::string line = strMap.substr(prevFoundIndex, strMap.find('\n', prevFoundIndex));
		prevFoundIndex = strMap.find('\n', prevFoundIndex) + 1;
		for(int x = 0; x < width; ++x) {
			Tile &tile = tiles[y][x];
			tile.setValue(height * y + x);

			// Determines what tile it is with asciis
			if(line[x] == '#') tile.setWall(true);
			else if(line[x] == 'S') setSource(x, y);
			else if(line[x] == 'D') setDest(x, y);
		}
	}
	
}

Grid::~Grid() {
	for(int y = 0; y < height; ++y) {
		delete tiles[y];
	}
	delete tiles;
}

int Grid::getWidth() {
	return width;
}

int Grid::getHeight() {
	return height;
}

Tile &Grid::getTileAt(int x, int y) {
	return tiles[y][x];
}

void Grid::randomizeTiles() {
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			Tile &tile = tiles[y][x];
			if(isSource(x, y) || isDest(x, y)) continue;
			if(rand() % 2 == 0) {
				tile.setWall(true);
			}
		}
	}
}

// Prints out the graph where # is a wall and ` is empty
std::ostream & operator<<(std::ostream &os, Grid &g) {
	for(int y = 0; y < g.getHeight(); ++y) {
		for(int x = 0; x < g.getWidth(); ++x) {
			Tile tile = g.getTileAt(x, y);
			// os << tile;
			char c = tile.isWall() ? '#' : '`';
			if(g.isSource(x, y)) c = 'S';
			else if(g.isDest(x, y)) c = 'D';
			os << c;
		}
		os << "\n";
	}
	return os;
}
