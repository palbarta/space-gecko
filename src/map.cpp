#include "map.h"

Map::Map(int width, int height)
	: width_(width)
	, height_(height)
	, mid_point_(width / 2.0f, height_ / 2.0f)
{
}

Map::~Map()
{
}