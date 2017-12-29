#include "map.h"

Map::Map(sf::Vector2u window_size)
	: width_(window_size.x)
	, height_(window_size.y)
	, mid_point_(width_ / 2.0f, height_ / 2.0f)
{
}