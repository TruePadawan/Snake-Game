#pragma once

#include "Snake.h"
#include "Location.h"

class Food
{
public:
	Food(const Location& _cordinate);
	void draw(Board& board);
	void setCordinate(const Location& _cordinate);
	bool isEaten(const Snake& player);

private:
	Location cordinate;
};

