#include "space_ship.h"
#include "map.h"

#include <cmath>

SceneObject::SceneObject(const Map& map)
	: map_(map)
{
}

float
SceneObject::angleRadian() const
{
	auto&& mid = map_.midPoint();
	auto&& pos = shape_.getPosition();
	const float dx = pos.x - mid.x;
	const float dy = pos.y - mid.y;
	const float angle = std::atan(dy / dx);
	return angle;
}

float
SceneObject::angleDegree() const
{
	return angleRadian() * 180 / 3.1415;
}

void
SceneObject::setAngleAndPosition(float angle)
{
	static const float radius = 250;
	auto&& mid = map_.midPoint();
	const float x = mid.x + std::cos(angle)*radius;
	const float y = mid.y + std::sin(angle)*radius;
	shape_.setPosition(x, y);
	shape_.setRotation(angle * 180 / 3.1415);
}

void
SceneObject::setAngleByPosition()
{
	shape_.setRotation(angleDegree());
}
