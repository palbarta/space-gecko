#pragma once

#include "scene_object.h"

class SpaceShip : public SceneObject
{
public:
	SpaceShip(const Map& map, float initial_angle);
	~SpaceShip();

	void update(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	bool shoot();

private:
	void setupShape();
	void move(float dt, int dir);

private:
	const float speed_{ 3.0f };
	float initial_angle_;

	// Shooting
	sf::Clock shooting_timer_;
	const sf::Time shooting_interval_ = sf::seconds(0.2f);
};

