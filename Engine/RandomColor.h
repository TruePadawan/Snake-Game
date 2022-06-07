#pragma once
#include "Colors.h"
#include <random>

class RandomColor
{
public:
	RandomColor();
	Color generate();
private:
	std::mt19937 RNG;
	std::uniform_int_distribution<int> RGB_DISTRIBUTION;
};

