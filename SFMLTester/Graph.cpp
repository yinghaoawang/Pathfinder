#include "Graph.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>

Graph::Graph(int w, int h) : width(w), height(h) {
	width = w;
	height = h;
	// Instantiate empty tiles with ascending values according to their x and yumns (see below comments)
	adj = new Tile*[height];
	for(int i = 0; i < height; ++i) {
		adj[i] = new Tile[width];
	}
	for(int x = 0; x < width; ++x) {
		for(int y = 0; y < height; ++y) {
			// i.e Value of a 3x3 map i (from bottom to top) 0 1 2, 3 4 5, 6 7 8
			adj[y][x].setValue(height * y + x);
		}
	}
}

bool Graph::isSource(int x, int y) {
	return source[0] == x && source[1] == y;
}

bool Graph::isDest(int x, int y) {
	return dest[0] == x && dest[1] == y;
}

// Parses a string # is a wall
Graph::Graph(std::string strMap) {
	// Determine the size of the graph by the size of the string delimited by \n
	height = std::count(strMap.begin(), strMap.end(), '\n');
	if(height != 0) {
		std::string firstRow = strMap.substr(0, strMap.find('\n'));
		width = firstRow.size();
	} else {
		width = 0;
	}

	// Instantiate blank tiles
	adj = new Tile*[height];
	for(int i = 0; i < height; ++i) {
		adj[i] = new Tile[width];
	}

	// Gets each x as strings delimited by newspace
	int prevFoundIndex = 0;
	for(int y = 0; y < height; ++y) {
		std::string line = strMap.substr(prevFoundIndex, strMap.find('\n', prevFoundIndex));
		prevFoundIndex = strMap.find('\n', prevFoundIndex) + 1;
		for(int x = 0; x < width; ++x) {
			adj[y][x].setValue(height * y + x);

			// Determines what tile it is with asciis
			if(line[x] == '#') adj[y][x].setWall(true);
			else if(line[x] == 'S') {
				source[0] = x;
				source[1] = y;
			} else if(line[x] == 'D') {
				dest[0] = x;
				dest[1] = y;
			}
		}
	}
	
}

int Graph::getWidth() {
	return width;
}

int Graph::getHeight() {
	return height;
}

Tile Graph::getTileAt(int x, int y) {
	return adj[y][x];
}

void Graph::randomizeTiles() {
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			// high 10, low 2
			//adj[i][j].setValue(rand() % (10 - 2 + 1) + 2);
			Tile &tile = adj[y][x];
			if(rand() % 2 == 0) {
				adj[y][x].setWall(true);
			}
		}
	}
}

// Prints out the graph where # is a wall and ` is empty
std::ostream & operator<<(std::ostream &os, Graph &g) {

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
