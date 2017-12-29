#include "space_ship.h"
#include "map.h"
#include "settings.h"

#include <SFML/Graphics.hpp>

SpaceShip::SpaceShip(const Map& map, float initial_angle)
	: SceneObject(map)
	, initial_angle_(initial_angle)
{
	setupShape();
	setPosition(initial_angle, 400);
	shooting_timer_.restart();
}

SpaceShip::~SpaceShip()
{
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

void
SpaceShip::update(float dt)
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

void
SpaceShip::move(float dt, int dir)
{
	const float angle_covered = dir * speed_ * dt;
	const float new_angle = initial_angle_ + angle_covered;
	initial_angle_ = new_angle;
	setPosition(new_angle, 400);
}

bool
SpaceShip::shoot()
{
	if (shooting_timer_.getElapsedTime() > shooting_interval_)
	{
		shooting_timer_.restart();
		return true;
	}

	return false;
}