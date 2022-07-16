#include "Obstacle.h"

Obstacle::Obstacle()
{
	coordinate = { 0, 0 };
}

Obstacle::Obstacle(Location coord)
	:coordinate(coord)
{
}

Location Obstacle::getLocation() const
{
	return coordinate;
}

void Obstacle::setDestroyed()
{
	coordinate = { 0, 0 };
}

bool Obstacle::isDestroyed() const
{
	return (coordinate.x == 0 && coordinate.y == 0);
}

void Obstacle::draw(Board& board) const
{
	int x = coordinate.x;
	int y = coordinate.y;

	board.drawCell({ x, y }, Colors::LightGray);
	/*for (int i = x; i < x + x_cellspace; i++)
	{
		for (int j = y; j < y + y_cellspace; j++)
		{
		}
	}*/
}
