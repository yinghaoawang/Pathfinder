#pragma once
#include <ostream>
class Tile {
private:
	bool wall;
	int value;

public:
	Tile();
	Tile(bool w, int v);
	~Tile();

	bool isWall();
	int getValue();

	void setWall(bool w);
	void setValue(int v);

	friend std::ostream& operator<<(std::ostream & os, Tile& t);
};