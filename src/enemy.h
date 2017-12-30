#pragma once

#include "scene_object.h"

class Enemy : public SceneObject
{
public:
	Enemy(const Map& map);
	void update(float dt);

private:
	void setupShape();
	void setInitialPosition();

private:
};