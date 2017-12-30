#pragma once

#include "scene_object.h"

struct SpaceShipConfig;

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
	const SpaceShipConfig& cfg_;
	float initial_angle_;

	// Shooting
	sf::Clock shooting_timer_;
};

