#include "enemy.h"

#include "asset_store.h"
#include "map.h"
#include "util.h"

#include <SFML/Graphics.hpp>

Enemy::Enemy(const Map& map)
	: SceneObject(map, -90.0f)
{
	setupShape();
	setupB2Shape();
	setInitialPosition();
}

void
Enemy::setupShape()
{
	auto&& texture_store = AssetStore::getInstance().textures();
	auto&& texture = RandomMinusOneToOne() > 0.0f ? &texture_store.enemy_a_texture_ : &texture_store.enemy_b_texture_;
	shape_.setTexture(texture, true);
	sf::Vector2f size(shape_.getTextureRect().width, shape_.getTextureRect().height);
	shape_.setSize(size);
	const float scale = 0.25f;
	shape_.setScale(scale, scale);
	shape_.setOrigin(shape_.getSize() / 2.f);
}

void 
Enemy::setInitialPosition()
{
	const sf::Vector2f offset(RandomMinusOneToOne() * 200, RandomMinusOneToOne() * 200);
	shape_.setPosition(map_.width() / 2.0f, map_.height() / 2.0f);
	shape_.move(offset);
	setRotation();
}

void
Enemy::update(float dt)
{
}