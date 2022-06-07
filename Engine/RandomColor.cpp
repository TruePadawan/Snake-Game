#include "RandomColor.h"

RandomColor::RandomColor()
	:RNG(std::random_device()()),
	RGB_DISTRIBUTION(0, 255)
{
}

Color RandomColor::generate()
{
	int R = RGB_DISTRIBUTION(RNG);
	int G = RGB_DISTRIBUTION(RNG);
	int B = RGB_DISTRIBUTION(RNG);
	return Color(R, G, B);
}
