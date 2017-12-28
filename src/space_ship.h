#pragma once

#include <SFML/Graphics.hpp>

class Map;

class SpaceShip
{
public:
	SpaceShip(const Map& map, float initial_angle);
	~SpaceShip();

	sf::RectangleShape& shape() { return shape_; }
	void moveLeft(float dt);
	void moveRight(float dt);

private:
	void setupShape();
	void move(float dt, int dir);

	float angle() const;
	void  setAngle(float angle);

private:
	const Map& map_;
	sf::RectangleShape shape_;

	const float speed_{ 3.0f };
	float initial_angle_;
};

