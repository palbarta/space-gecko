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
	object_scale_ = 0.25f;
	radial_position_ = cfg_.radius_fraction_to_edge_of_screen_;
	setupShape();
	setupB2Shape();
	setPosition(initial_angle, radial_position_);
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
	shape_.setOrigin(shape_.getSize() / 2.f);
	setScale();
}

void
SpaceShip::update(float dt)
{
}

void
SpaceShip::moveLeft(float dt)
{
	angularMove(dt, -1);
}

void
SpaceShip::moveRight(float dt)
{
	angularMove(dt, 1);
}

void SpaceShip::moveInwards(float dt)
{
	radialMove(dt, 1);
}

void SpaceShip::moveOutwards(float dt)
{
	radialMove(dt, -1);
}

void
SpaceShip::angularMove(float dt, int dir)
{
	const float angle_covered = dir * cfg_.angular_speed_ * dt;
	const float new_angle = initial_angle_ + angle_covered;
	initial_angle_ = new_angle;
	setPosition(new_angle, radial_position_);
}


void
SpaceShip::radialMove(float dt, int dir)
{
	radial_position_ += dir * cfg_.radial_speed_ * dt;
	// TODO: move to common
	radial_position_ = std::min(std::max(0.2f, radial_position_), 0.9f);
	setPosition(initial_angle_, radial_position_);
	setScale();
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