#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>
#include <vector>

class Board
{
public:
	Board(Graphics& _gfx, int _borderWidth = 5, int _margin = 5);
	void drawCell(const Location& cordinates, Color c);
	void spawnObstacle(std::mt19937& rng, const class Food& food, const class Snake& player);
	bool checkForObstacle(const Location& loc);
	void drawObstacles();
	void drawBoundary();
public:
	static constexpr int CELL_DIMENSION = 20;
	static constexpr int CELL_PER_WIDTH = 39;
	static constexpr int CELL_PER_HEIGHT = 29;
private:
	Graphics& gfx;
	Color borderColor;
	int borderWidth;
	int margin;
	int cellPadding;

	std::vector<Location> obstacleLocations;
	bool obstacles[CELL_PER_WIDTH][CELL_PER_HEIGHT] = { false };
	std::uniform_int_distribution<int> xDist{ 0, CELL_PER_WIDTH - 1 };
	std::uniform_int_distribution<int> yDist{ 0, CELL_PER_HEIGHT - 1 };

};

