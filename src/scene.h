#pragma once
#include <SFML/Graphics.hpp>

#include "map.h"
#include "space_ship.h"

#include <list>

class Scene
{
public:
	Scene(sf::Vector2u window_size);

	void moveSpaceShipClockwise(float dt);
	void moveSpaceShipCounterClockwise(float dt);
	void shootWithSpaceShip(float dt);
	void update(float dt);
	const std::list<SceneObject*>& objects() const { return objects_; }
	const sf::Color& backgroundColor() const { return map_.backgroundColor(); }

protected:
	const Map map_;
	SpaceShip space_ship_;
	std::list<SceneObject*> objects_;
};