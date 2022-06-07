#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& _gfx, int _borderWidth = 5, int _margin = 5);
	void drawCell(const Location& cordinates, Color c);
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
};

