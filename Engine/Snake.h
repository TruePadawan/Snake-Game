#pragma once

#include "Board.h"
#include "RandomColor.h"

class Snake
{
public:
	Snake(const Location& cordinate);
	void moveBy(const Location& delta_location);
	void grow();
	void draw(Board& board) const;
	Location getHeadCordinate() const;
	bool isAtBoundary();
	bool collideWithSelf() const;
	bool checkForCollision(const Location &target) const;
private:
	class Segment
	{
		friend class Snake;
	public:
		void initHead(const Location& _cordinate);
		void initBody();
		void follow(const Segment& next);
		void moveBy(const Location& delta_location);
		void draw(Board& board) const;
	private:
		RandomColor randomColorGenerator{};
		Location cordinate;
		Color segmentColor;
	};
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};

