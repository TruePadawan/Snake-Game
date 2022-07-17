#include "Board.h"
#include "Food.h"
#include "Snake.h"
#include <assert.h>

Board::Board(Graphics& _gfx, int _borderWidth , int _margin)
	:gfx(_gfx), borderColor(Colors::Red)
{
	borderWidth = _borderWidth;
	margin = _margin;
	cellPadding = 2;
}

void Board::drawCell(const Location& cordinates, Color c)
{
	assert(cordinates.x >= 0);
	assert(cordinates.x < CELL_PER_WIDTH);
	assert(cordinates.y >= 0);
	assert(cordinates.y < CELL_PER_HEIGHT);

	int xCord = cordinates.x * CELL_DIMENSION + margin + borderWidth + cellPadding;
	int yCord = cordinates.y * CELL_DIMENSION + margin + borderWidth + cellPadding;
	gfx.DrawRectDim(xCord, yCord, CELL_DIMENSION - cellPadding, CELL_DIMENSION - cellPadding, c);
}

void Board::spawnObstacle(std::mt19937& rng, const Food& food, const Snake& player)
{
	Location obsLoc{ 0,0 };
	do
	{
		obsLoc.x = xDist(rng);
		obsLoc.y = yDist(rng);
	} while (player.checkForCollision(obsLoc) || food.cordinate == obsLoc);

	obstacleLocations.push_back(obsLoc);
	obstacles[obsLoc.x][obsLoc.y] = true;
}

bool Board::checkForObstacle(const Location& loc)
{
	return obstacles[loc.x][loc.y];
}

void Board::drawObstacles()
{
	for (const Location& obsLoc : obstacleLocations)
	{
		drawCell(obsLoc, Colors::Gray);
	}
}


void Board::drawBoundary()
{
	// TOP RECT
	int rectWidth = Graphics::ScreenWidth - (margin * 2);
	gfx.DrawRectDim(margin, margin, rectWidth, borderWidth, borderColor);

	// LEFT RECT
	int rectHeight = Graphics::ScreenHeight - (margin * 2) - (borderWidth * 2);
	gfx.DrawRectDim(margin, margin + borderWidth, borderWidth, rectHeight, borderColor);

	// RIGHT RECT
	int rightOffset = margin + rectWidth - borderWidth;
	gfx.DrawRectDim(rightOffset, margin + borderWidth, borderWidth, rectHeight, borderColor);

	// BOTTOM RECT
	int topOffset = margin + borderWidth + rectHeight;
	gfx.DrawRectDim(margin, topOffset, rectWidth, borderWidth, borderColor);
}
