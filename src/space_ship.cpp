#include "space_ship.h"

#include "asset_store.h"
#include "config.h"
#include "map.h"

#include <SFML/Graphics.hpp>

SpaceShip::SpaceShip(const Map& map, float initial_angle)
	: SceneObject(map, -90.0f)
	, cfg_(Config::getInstance().space_ship_)
	, initial_angle_(initial_angle)
{
	setupShape();
	setupB2Shape();
	setPosition(initial_angle, cfg_.radius_fraction_to_edge_of_screen_);
	shooting_timer_.restart();
}

SpaceShip::~SpaceShip()
{
}

void
SpaceShip::setupShape()
{
	shape_.setTexture(&AssetStore::getInstance().textures().space_ship_texture_, true);
	sf::Vector2f size(shape_.getTextureRect().width, shape_.getTextureRect().height);
	shape_.setSize(size);
	const float scale = 0.25f;
	shape_.setScale(scale, scale);
	shape_.setOrigin(shape_.getSize() / 2.f);
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
	const float angle_covered = dir * cfg_.speed_ * dt;
	const float new_angle = initial_angle_ + angle_covered;
	initial_angle_ = new_angle;
	setPosition(new_angle, cfg_.radius_fraction_to_edge_of_screen_);
}

bool
SpaceShip::shoot()
{
	if (shooting_timer_.getElapsedTime() > cfg_.shooting_interval_in_seconds_)
	{
		shooting_timer_.restart();
		return true;
	}

	return false;
}