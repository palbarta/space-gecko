#include "scene.h"

#include "bullet.h"
#include "enemy.h"
#include "star.h"

#include "Box2D/Collision/b2Collision.h"

#include <iostream>

namespace {

template<typename T>
void
RemoveDestroyedObjectsFromList(std::list<T*>& objects, bool delete_object)
{
	auto it = objects.begin();
	while (it != objects.end()) {
		const T* object = *it;
		if (!object->isAlive()) {
			it = objects.erase(it);
			if (delete_object)
				delete object;
		}
		else {
			++it;
		}
	}
}

}

Scene::Scene(sf::Vector2u window_size)
	: map_(window_size)
	, space_ship_(map_, 0)
{
	const int number_of_stars = 100;
	for (int i = 0; i < number_of_stars; ++i) {
		objects_.push_back(new Star(map_));
	}

	const int number_of_enemies = 5;
	for (int i = 0; i < number_of_enemies; ++i) {
		Enemy* enemy = new Enemy(map_);
		enemies_.push_back(enemy);
		objects_.push_back(enemy);
	}

	objects_.push_back(&space_ship_);
}

Scene::~Scene()
{
	// TODO: Memory leak for dynamic objects
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
Scene::moveSpaceShipInwards(float dt)
{
	space_ship_.moveInwards(dt);
}

void 
Scene::moveSpaceShipOutwards(float dt)
{
	space_ship_.moveOutwards(dt);
}

void
Scene::shootWithSpaceShip(float dt)
{
	if (space_ship_.shoot()) {
		Bullet* bullet = new Bullet(map_, space_ship_);
		bullets_.push_back(bullet);
		objects_.push_back(bullet);
	}
}

void 
Scene::update(float dt)
{
	std::for_each(objects_.begin(), objects_.end(), [dt](auto* obj) { obj->update(dt); });
	handleCollisions();
	removeDestroyedObjects();
}

void
Scene::removeDestroyedObjects()
{
	RemoveDestroyedObjectsFromList<Bullet>(bullets_, false);
	RemoveDestroyedObjectsFromList<Enemy>(enemies_, false);
	RemoveDestroyedObjectsFromList<SceneObject>(objects_, true);
}

void
Scene::handleCollisions()
{
	for (auto&& bullet : bullets_) {
		for (auto&& enemy : enemies_) {
			if (doCollide(*bullet, *enemy)) {
				bullet->destroy();
				enemy->destroy();
			}
		}
	}
}


bool Scene::doCollide(const SceneObject& obj_a, const SceneObject& obj_b) const
{
	return b2TestOverlap(&obj_a.box2dShape(), 0, &obj_b.box2dShape(), 0, obj_a.box2dTransform(), obj_b.box2dTransform());
}
