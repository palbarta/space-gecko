#pragma once

#include "scene_object.h"

class Star : public SceneObject
{
public:
	Star(const Map& map);
	~Star();
	void update(float dt);

private:
	void setupShape();
	void setInitialPosition();
	bool outsideOfMapLimits() const;
	void reset();
	float calcAge() const;

private:
	sf::Vector2f direction_;
	const float acceleration_ { 1000.0f };
	float speed_ { 0.0f };
	sf::Color color_ {255, 255, 255, 0};
	float age_ { 0.0f };
};