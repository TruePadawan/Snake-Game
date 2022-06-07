#pragma once

struct Location
{
	int x;
	int y;
	void add(const Location& cordinate)
	{
		x += cordinate.x;
		y += cordinate.y;
	}
	bool operator==(const Location& other) const
	{
		return ((this->x == other.x) && (this->y == other.y));
	}
};

