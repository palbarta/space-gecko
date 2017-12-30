#include "util.h"


#include <cmath>

float
RandomMinusOneToOne()
{
	return ((double)std::rand()) / RAND_MAX * 2.0f - 1.0f;
}

sf::Vector2f
RandomDirection()
{
	return sf::Vector2f(RandomMinusOneToOne(), RandomMinusOneToOne());
}