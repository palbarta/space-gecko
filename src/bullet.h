#pragma once

#include "scene_object.h"

class SpaceShip;

class Bullet : public SceneObject
{
public:
	Bullet(const Map& map, const SpaceShip& owner);
	~Bullet();
	void update(float dt);

private:
	void setupShape();
	bool outsideOfMapLimits() const;

private:
	const sf::Vector2f direction_;
	const float speed_ { 500.0f };
};