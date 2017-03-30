#include "Graph.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>

Graph::Graph(int r, int c) : rows(r), cols(c) {
	// Instantiate empty tiles with ascending values according to their row and columns (see below comments)
	adj = new Tile*[r];
	for(int i = 0; i < r; ++i) {
		adj[i] = new Tile[c];
	}
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			// i.e Value of a 3x3 map i (from bottom to top) 0 1 2, 3 4 5, 6 7 8
			adj[i][j].setValue(cols * i + j);
		}
	}
}

bool Graph::isSource(int row, int col) {
	return source[0] == row && source[1] == col;
}

bool Graph::isDest(int row, int col) {
	return dest[0] == row && dest[1] == col;
}

// Parses a string # is a wall
Graph::Graph(std::string strMap) {
	// Determine the size of the graph by the size of the string delimited by \n
	rows = std::count(strMap.begin(), strMap.end(), '\n');
	if(rows != 0) {
		std::string firstRow = strMap.substr(0, strMap.find('\n'));
		cols = firstRow.size();
	} else {
		cols = 0;
	}

	// Instantiate blank tiles
	adj = new Tile*[rows];
	for(int i = 0; i < rows; ++i) {
		adj[i] = new Tile[cols];
	}

	// Gets each row as strings delimited by newspace
	int prevFoundIndex = 0;
	for(int i = 0; i < rows; ++i) {
		std::string line = strMap.substr(prevFoundIndex, strMap.find('\n', prevFoundIndex));
		prevFoundIndex = strMap.find('\n', prevFoundIndex) + 1;
		for(int j = 0; j < cols; ++j) {
			adj[i][j].setValue(cols * i + j);

			// Determines what tile it is with asciis
			if(line[j] == '#') adj[rows - i - 1][j].setWall(true);
			else if(line[j] == 'S') {
				source[0] = rows - i - 1;
				source[1] = j;
			} else if(line[j] == 'D') {
				dest[0] = rows - i - 1;
				dest[1] = j;
			}
		}
	}
	
}

int Graph::getRows() {
	return rows;
}

int Graph::getCols() {
	return cols;
}

Tile Graph::getTileAt(int r, int c) {
	return adj[r][c];
}

void Graph::randomizeTiles() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			// high 10, low 2
			//adj[i][j].setValue(rand() % (10 - 2 + 1) + 2);
			Tile &tile = adj[i][j];
			if(rand() % 2 == 0) {
				adj[i][j].setWall(true);
			}
		}
	}
}

// Prints out the graph where # is a wall and ` is empty
std::ostream & operator<<(std::ostream &os, Graph &g) {
	for (int i = g.getRows() - 1; i >= 0; --i) {
		for (int j = 0; j < g.getCols(); ++j) {
			Tile tile = g.getTileAt(i, j);
			// os << tile;
			char c = tile.isWall() ? '#' : '`';
			if(g.isSource(i, j)) c = 'S';
			else if(g.isDest(i, j)) c = 'D';
			os << c;
		}
		os << "\n";
	}
	return os;
}
