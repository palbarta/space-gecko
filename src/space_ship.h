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
	void moveInwards(float dt);
	void moveOutwards(float dt);
	void radialMove(float dt, int dir);
	bool shoot();

private:
	void setupShape();
	void angularMove(float dt, int dir);

private:
	const SpaceShipConfig& cfg_;
	float initial_angle_;

	// Shooting
	sf::Clock shooting_timer_;
};

