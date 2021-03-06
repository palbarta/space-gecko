#include "space_ship.h"
#include "map.h"

#include <cmath>

constexpr double pi = 3.141592653589793;

SceneObject::SceneObject(const Map& map, float shape_rotation)
	: map_(map)
	, shape_rotation_(shape_rotation)
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
SceneObject::setAbsolutePosition(float angle, float radius)
{
	auto&& mid = map_.midPoint();
	const float x = mid.x + std::cos(angle * pi / 180)*radius;
	const float y = mid.y + std::sin(angle * pi / 180)*radius;
	shape_.setPosition(x, y);
	shape_.setRotation(shape_rotation_ + angle);
}

float 
SceneObject::radialPosition() const
{
	auto&& pos = shape_.getPosition();
}

float 
SceneObject::angularPosition() const
{
	return 0.0f;
}

const b2Transform
SceneObject::box2dTransform() const
{
	b2Transform transform;
	auto&& pos_a = shape_.getPosition();
	transform.Set(b2Vec2(pos_a.x, pos_a.y), shape_.getRotation() * pi / 180);
	return transform;
}

void
SceneObject::setPosition(float angle, float radius_fraction)
{
	const float radius = radius_fraction * std::min(map_.width(), map_.height()) * 0.5f;
	setAbsolutePosition(angle, radius);
}

void
SceneObject::move(float d_angle, float d_radius)
{

}
/*
void
SceneObject::setRotation()
{
	shape_.setRotation(shape_rotation_ + inwardAngleDegree());
}

void
SceneObject::setScale()
{
	shape_.setScale(object_scale_ * radialPosition(), object_scale_ * radialPosition());
}*/

bool
SceneObject::outsideOfMapLimits() const
{
	return shape_.getPosition().x < 0 || shape_.getPosition().x > map_.width() ||
		shape_.getPosition().y < 0 || shape_.getPosition().y > map_.height();
}

void
SceneObject::setupB2Shape()
{
	b2_shape_.SetAsBox(shape_.getSize().x * shape_.getScale().x / 2.0f, shape_.getSize().y * shape_.getScale().y / 2.0f);
}