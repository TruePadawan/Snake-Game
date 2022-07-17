#pragma once

#include "Snake.h"
#include "Location.h"
#include <random>

class Food
{
public:
	Food(std::mt19937& rng);
	void draw(Board& board);
	void respawn(std::mt19937& rng);
	bool isEaten(const Snake& player);
public:
	Location cordinate;
private:
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
};

