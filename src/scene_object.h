#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

class Map;

class SceneObject
{
public:
	SceneObject(const Map& map, float shape_rotation = 0.0f);
	virtual ~SceneObject() {};
	const sf::RectangleShape& shape() const { return shape_; }
	virtual void update(float dt) = 0;
	float inwardAngleRadian() const;
	float inwardAngleDegree() const;
	sf::Vector2f inwardDirection() const;
	bool isAlive() const { return is_alive_; }
	void destroy() { is_alive_ = false; }

	const b2PolygonShape& box2dShape() const { return b2_shape_; }
	const b2Transform box2dTransform() const;

protected:
	void setPosition(float angle, float radius_fraction);
	void move(float d_angle, d_radius);
	//void setRotation();
	//void setScale();
	bool outsideOfMapLimits() const;
	void setupB2Shape();

private:
	void setAbsolutePosition(float angle, float radius);
	float radialPosition() const;
	float angularPosition() const;

protected:
	sf::RectangleShape shape_;
	const Map& map_;
	const float shape_rotation_;
	b2PolygonShape b2_shape_;
	bool is_alive_{ true };
	float object_scale_ { 1.0f };
	float radial_direction_  { 0.0f };
	float angular_direction_ { 0.0f };
};