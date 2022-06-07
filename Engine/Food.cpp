#include "Food.h"

Food::Food()
	:random_num_generator(std::random_device()()),
	xDist(0, 38),
	yDist(0, 28)
{
	cordinate = { xDist(random_num_generator), yDist(random_num_generator) };
}

void Food::draw(Board& board)
{
	board.drawCell(cordinate, Colors::Gray);
}

void Food::respawn()
{
	cordinate = { xDist(random_num_generator), yDist(random_num_generator) };
}

bool Food::isEaten(const Snake& player)
{
	Location playerCord = player.getHeadCordinate();
	return playerCord == cordinate;
}
