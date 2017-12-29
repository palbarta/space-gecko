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

private:
	const sf::Vector2f direction_;
	const float speed_ { 2000.0f };
};