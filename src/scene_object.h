#pragma once
#include <SFML/Graphics.hpp>

class Map;

class SceneObject
{
public:
	SceneObject(const Map& map);
	const sf::RectangleShape& shape() const { return shape_; }
	virtual void update(float dt) = 0;
	float inwardAngleRadian() const;
	float inwardAngleDegree() const;
	sf::Vector2f inwardDirection() const;
	bool isActive() const { return is_active_; }

protected:
	void  setPosition(float angle, float radius);
	void  setRotation();
	bool outsideOfMapLimits() const;

protected:
	const Map& map_;
	sf::RectangleShape shape_;
	bool is_active_{ true };
};