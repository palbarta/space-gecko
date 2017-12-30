#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

class Map;

class SceneObject
{
public:
	SceneObject(const Map& map);
	const sf::RectangleShape& shape() const { return shape_; }
	const b2PolygonShape& b2Shape() const { return b2_shape_; }
	virtual void update(float dt) = 0;
	float inwardAngleRadian() const;
	float inwardAngleDegree() const;
	sf::Vector2f inwardDirection() const;
	bool isAlive() const { return is_alive_; }
	void destroy() { is_alive_ = false; }

protected:
	void  setPosition(float angle, float radius_fraction);
	void  setRotation();
	bool outsideOfMapLimits() const;
	void setupB2Shape();

private:
	void  setAbsolutePosition(float angle, float radius);

protected:
	const Map& map_;
	sf::RectangleShape shape_;
	b2PolygonShape b2_shape_;
	bool is_alive_{ true };
};