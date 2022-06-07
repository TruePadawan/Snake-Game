#include "Food.h"

Food::Food(const Location& _cordinate)
{
	cordinate = _cordinate;
}

void Food::draw(Board& board)
{
	board.drawCell(cordinate, Colors::Gray);
}

void Food::setCordinate(const Location& _cordinate)
{
	cordinate = _cordinate;
}

bool Food::isEaten(const Snake& player)
{
	Location playerCord = player.getHeadCordinate();
	return playerCord == cordinate;
}
