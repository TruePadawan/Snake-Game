#pragma once

#include "Snake.h"
#include "Location.h"
#include <random>

class Food
{
public:
	Food();
	void draw(Board& board);
	void respawn();
	bool isEaten(const Snake& player);
public:
	Location cordinate;
private:
	std::mt19937 random_num_generator;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
};

