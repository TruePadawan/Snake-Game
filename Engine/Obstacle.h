#pragma once

#include "Location.h"
#include "Board.h"

class Obstacle
{
public:
	Obstacle();
	Obstacle(Location coord);
	Location getLocation() const;
	void setDestroyed();
	bool isDestroyed() const;
	void draw(Board& board) const;
private:
	Location coordinate;
};

