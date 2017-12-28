#include "space_ship.h"
#include "map.h"

#include <SFML/Graphics.hpp>


SpaceShip::SpaceShip(const Map& map, float initial_angle)
	: map_(map)
	, initial_angle_(initial_angle)
{
	setupShape();
	setAngle(initial_angle);
}

void
SpaceShip::setupShape()
{
	sf::Vector2f size(25, 100);
	shape_.setSize(size - sf::Vector2f(3, 3));
	shape_.setOutlineThickness(3);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setFillColor(sf::Color(200, 100, 100));
	shape_.setOrigin(size / 2.f);
}

SpaceShip::~SpaceShip()
{
}

void
SpaceShip::moveLeft(float dt)
{
	move(dt, -1);
}

void
SpaceShip::moveRight(float dt)
{
	move(dt, 1);
}

float
SpaceShip::angle() const
{
	auto&& mid = map_.midPoint();
	auto&& pos = shape_.getPosition();
	const float dx = pos.x - mid.x;
	const float dy = pos.y - mid.y;
	const float angle = tan(dy / dx);
	return angle;
}

void
SpaceShip::setAngle(float angle)
{
	static const float radius = 250;
	auto&& mid = map_.midPoint();
	const float x = mid.x + cos(angle)*radius;
	const float y = mid.y + sin(angle)*radius;
	shape_.setPosition(x, y);
	shape_.setRotation(angle * 180 / 3.1415);
}

void
SpaceShip::move(float dt, int dir)
{
	const float angle_covered = dir * speed_ * dt;
	const float new_angle = initial_angle_ + angle_covered;
	initial_angle_ = new_angle;
	setAngle(new_angle);
}