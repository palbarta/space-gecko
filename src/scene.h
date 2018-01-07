#pragma once
#include <SFML/Graphics.hpp>

#include "map.h"
#include "space_ship.h"

#include <list>

class Bullet;
class Enemy;

class Scene
{
public:
	Scene(sf::Vector2u window_size);

	void moveSpaceShipClockwise(float dt);
	void moveSpaceShipCounterClockwise(float dt);
	void moveSpaceShipInwards(float dt);
	void moveSpaceShipOutwards(float dt);
	void shootWithSpaceShip(float dt);
	void update(float dt);
	void handleCollisions();
	const std::list<SceneObject*>& objects() const { return objects_; }
	const sf::Color& backgroundColor() const { return map_.backgroundColor(); }
	
private:
	void removeDestroyedObjects();
	bool doCollide(const SceneObject& obj1, const SceneObject& obj2) const;

protected:
	const Map map_;
	SpaceShip space_ship_;
	std::list<SceneObject*> objects_;
	std::list<Bullet*> bullets_;
	std::list<Enemy*> enemies_;
};