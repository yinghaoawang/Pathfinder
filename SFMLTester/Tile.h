#pragma once
#include <ostream>
class Tile {
private:
	bool wall;
	int value;
	bool visited;

public:
	Tile();
	Tile(bool w, int v);
	~Tile();

	bool isWall();
	int getValue();
	bool isVisited();

	void setWall(bool w);
	void setValue(int v);
	void setVisited(int v);

	friend std::ostream& operator<<(std::ostream & os, Tile& t);
};