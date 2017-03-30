#include "Graph.h"
#include <iostream>
#include <random>

Graph::Graph(int r, int c) : rows(r), cols(c) {
	adj = new Tile*[r];
	for(int i = 0; i < r; ++i) {
		adj[i] = new Tile[c];
	}
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			// high 10, low 2
			adj[i][j].setValue(cols * i + j);
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

std::ostream & operator<<(std::ostream &os, Graph &g) {
	for (int i = g.getRows() - 1; i >= 0; --i) {
		for (int j = 0; j < g.getCols(); ++j) {
			Tile tile = g.getTileAt(i, j);
			// os << tile;
			os << (tile.isWall() ? "`" : "#");
		}
		os << "\n";
	}
	return os;
}
