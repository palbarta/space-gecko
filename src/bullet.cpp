#include "bullet.h"
#include "map.h"
#include "space_ship.h"

#include <SFML/Graphics.hpp>

#include <cmath>


Bullet::Bullet(const Map& map, const SpaceShip& owner)
	: SceneObject(map)
	, direction_(std::cos(owner.angleRadian()), std::sin(owner.angleRadian()))
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
		return;
	}
	
	float x_offset = direction_.x * speed_ * dt;
	float y_offset = direction_.y * speed_ * dt;
	shape_.move(x_offset, y_offset);
}

bool
Bullet::outsideOfMapLimits() const
{
	return shape_.getPosition().x < 0 || shape_.getPosition().x > map_.width() ||
		   shape_.getPosition().y < 0 || shape_.getPosition().y > map_.height();
}