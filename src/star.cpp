#include "star.h"
#include "map.h"

#include <SFML/Graphics.hpp>

#include <cmath>

float
RandomMinusOneToOne()
{
	return ((double)std::rand()) / RAND_MAX * 2.0f - 1.0f;
}

sf::Vector2f 
RandomDirection()
{
	return sf::Vector2f(RandomMinusOneToOne(), RandomMinusOneToOne());
}

Star::Star(const Map& map)
	: SceneObject(map)
{
	reset();
	setupShape();
	setInitialPosition();
}

Star::~Star()
{
}

void
Star::setupShape()
{
	sf::Vector2f size(2, 2);
	shape_.setSize(size);
	shape_.setOutlineThickness(0);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOrigin(size / 2.f);
}

void 
Star::setInitialPosition()
{
	static const int offset = 10;
	shape_.setPosition(map_.width() / 2.0f + offset * direction_.x, map_.height() / 2.0f + offset * direction_.y);
}

void
Star::update(float dt)
{
	if (outsideOfMapLimits()) {
		reset();
		return;
	}
	
	speed_ += acceleration_ * dt; 
	float x_offset = direction_.x * speed_ * dt;
	float y_offset = direction_.y * speed_ * dt;
	shape_.move(x_offset, y_offset);
	age_ = calcAge();
	color_.a = age_ * 255.0f;
	shape_.setFillColor(color_);
	setAngleByPosition();
	shape_.setSize(sf::Vector2f(2 + age_ * 20, 2));
}

bool
Star::outsideOfMapLimits() const
{
	return shape_.getPosition().x < 0 || shape_.getPosition().x > map_.width() ||
		   shape_.getPosition().y < 0 || shape_.getPosition().y > map_.height();
}

void 
Star::reset()
{
	color_.a = 0;
	shape_.setFillColor(color_);
	direction_ = RandomDirection();
	speed_ = 0.0f;
	setInitialPosition();	
}

float
Star::calcAge() const 
{
	auto&& pos = shape_.getPosition();
	auto&& rel_pos = sf::Vector2f(pos.x / map_.width(), pos.y / map_.height());
	float x_age = rel_pos.x < 0.5f ? (0.5f - rel_pos.x) * 2.0f : (rel_pos.x - 0.5f) * 2.0f;
	float y_age = rel_pos.y < 0.5f ? (0.5f - rel_pos.y) * 2.0f : (rel_pos.y - 0.5f) * 2.0f;
	return std::max(x_age, y_age);
}