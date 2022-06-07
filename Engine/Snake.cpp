#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& cordinate)
{
	segments[0].initHead(cordinate);
}

void Snake::moveBy(const Location& delta_location)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].follow(segments[i - 1]);
	}
	segments[0].moveBy(delta_location);
}

void Snake::grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].initBody();
		++nSegments;
	}
}

void Snake::draw(Board& board) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].draw(board);
	}
}

Location Snake::getHeadCordinate() const
{
	return segments[0].cordinate;
}

bool Snake::isAtBoundary()
{
	const Location playerCord = this->getHeadCordinate();
	return ((playerCord.x == Board::CELL_PER_WIDTH) ||
		(playerCord.y == Board::CELL_PER_HEIGHT) ||
		(playerCord.x < 0 || playerCord.y < 0));
}

bool Snake::checkForCollision(const Location& target) const
{
	if (nSegments == 1) return false;
	for (int i = 1; i < nSegments; ++i)
	{
		if (segments[i].cordinate == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::initHead(const Location& _cordinate)
{
	cordinate = _cordinate;
	segmentColor = Snake::headColor;
}

void Snake::Segment::initBody()
{
	segmentColor = randomColorGenerator.generate();
}

void Snake::Segment::follow(const Segment& next)
{
	cordinate = next.cordinate;
}

void Snake::Segment::moveBy(const Location& delta_location)
{
	assert(abs(delta_location.x) + abs(delta_location.y) == 1);
	cordinate.add(delta_location);
}

void Snake::Segment::draw(Board& board) const
{
	board.drawCell(cordinate, segmentColor);
}
