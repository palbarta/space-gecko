#pragma once
#include <SFML/Graphics.hpp>

class Map;

class SceneObject
{
public:
	SceneObject(const Map& map);
	const sf::RectangleShape& shape() const { return shape_; }
	virtual void update(float dt) = 0;
	float angleRadian() const;
	float angleDegree() const;

protected:
	void  setAngleAndPosition(float angle);
	void  setAngleByPosition();

protected:
	const Map& map_;
	sf::RectangleShape shape_;
};