#include "enemy.h"
#include "map.h"
#include "util.h"

#include <SFML/Graphics.hpp>

Enemy::Enemy(const Map& map)
	: SceneObject(map)
{
	setupShape();
	setupB2Shape();
	setInitialPosition();
}

void
Enemy::setupShape()
{
	sf::Vector2f size(20, 20);
	shape_.setSize(size);
	shape_.setOutlineThickness(0);
	shape_.setOutlineColor(sf::Color::Magenta);
	shape_.setFillColor(sf::Color::Magenta);
	shape_.setOrigin(size / 2.f);
}

void 
Enemy::setInitialPosition()
{
	const sf::Vector2f offset(RandomMinusOneToOne() * 200, RandomMinusOneToOne() * 200);
	shape_.setPosition(map_.width() / 2.0f, map_.height() / 2.0f);
	shape_.move(offset);
}

void
Enemy::update(float dt)
{
}