#include "scene.h"

#include "bullet.h"
#include "star.h"

Scene::Scene(sf::Vector2u window_size)
	: map_(window_size)
	, space_ship_(map_, 0)
{
	const int number_of_stars = 100;
	for (int i = 0; i < number_of_stars; ++i) {
		objects_.push_back(new Star(map_));
	}

	objects_.push_back(&space_ship_);
}

void
Scene::moveSpaceShipClockwise(float dt)
{
	space_ship_.moveLeft(dt);
}

void
Scene::moveSpaceShipCounterClockwise(float dt)
{
	space_ship_.moveRight(dt);
}

void
Scene::shootWithSpaceShip(float dt)
{
	if (space_ship_.shoot()) {
		objects_.push_back(new Bullet(map_, space_ship_));
	}
}

void 
Scene::update(float dt)
{
	auto it = objects_.begin();
	while (it != objects_.end()) {
		auto&& object = *it;
		object->update(dt);
		if (!object->isActive()) {
			it = objects_.erase(it);
		}
		else {
			++it;
		}
	}
}
