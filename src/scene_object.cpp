#include "space_ship.h"
#include "map.h"

#include <cmath>

constexpr double pi = 3.141592653589793;

SceneObject::SceneObject(const Map& map)
	: map_(map)
{
}

float
SceneObject::inwardAngleRadian() const
{
	auto&& mid = map_.midPoint();
	auto&& pos = shape_.getPosition();
	const float dx = pos.x - mid.x;
	const float dy = pos.y - mid.y;
	const float angle = std::atan(dy / dx);
	const float final_angle = dx > 0.0f ? pi + angle : angle;
	return final_angle;
}

float
SceneObject::inwardAngleDegree() const
{
	return inwardAngleRadian() * 180 / pi;
}

sf::Vector2f
SceneObject::inwardDirection() const
{
	return sf::Vector2f(std::cos(inwardAngleRadian()), std::sin(inwardAngleRadian()));
}

void
SceneObject::setPosition(float angle, float radius)
{
	auto&& mid = map_.midPoint();
	const float x = mid.x + std::cos(angle)*radius;
	const float y = mid.y + std::sin(angle)*radius;
	shape_.setPosition(x, y);
	shape_.setRotation(angle * 180 / pi);
}

void
SceneObject::setRotation()
{
	shape_.setRotation(inwardAngleDegree());
}

bool
SceneObject::outsideOfMapLimits() const
{
	return shape_.getPosition().x < 0 || shape_.getPosition().x > map_.width() ||
		shape_.getPosition().y < 0 || shape_.getPosition().y > map_.height();
}