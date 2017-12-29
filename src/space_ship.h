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

private:
	void setupShape();
	void move(float dt, int dir);

private:
	const float speed_{ 3.0f };
	float initial_angle_;
};

