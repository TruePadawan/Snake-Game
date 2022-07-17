#include "Food.h"
#include "Board.h"

Food::Food(std::mt19937& rng)
	:xDist(0, Board::CELL_PER_WIDTH - 1), yDist(0, Board::CELL_PER_HEIGHT - 1)
{
	respawn(rng);
}

void Food::draw(Board& board)
{
	board.drawCell(cordinate, Colors::Green);
}

void Food::respawn(std::mt19937& rng)
{
	cordinate = { xDist(rng), yDist(rng) };
}

bool Food::isEaten(const Snake& player)
{
	Location playerCord = player.getHeadCordinate();
	return playerCord == cordinate;
}
