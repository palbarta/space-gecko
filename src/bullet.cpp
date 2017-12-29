#include "bullet.h"
#include "map.h"
#include "space_ship.h"

#include <SFML/Graphics.hpp>


Bullet::Bullet(const Map& map, const SpaceShip& owner)
	: SceneObject(map)
	, direction_(owner.inwardDirection())
{
	setupShape();
	shape_.setPosition(owner.shape().getPosition());
}

Bullet::~Bullet()
{
}

void
Bullet::setupShape()
{
	sf::Vector2f size(10, 10);
	shape_.setSize(size);
	shape_.setFillColor(sf::Color::Red);
	shape_.setOrigin(size / 2.f);
}

void
Bullet::update(float dt)
{
	if (outsideOfMapLimits()) {
		is_active_ = false;
		return;
	}
	
	float x_offset = direction_.x * speed_ * dt;
	float y_offset = direction_.y * speed_ * dt;
	shape_.move(x_offset, y_offset);
}