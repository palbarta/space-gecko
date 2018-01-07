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
	object_scale_ = 0.25f;
	auto&& texture_store = AssetStore::getInstance().textures();
	auto&& texture = RandomMinusOneToOne() > 0.0f ? &texture_store.enemy_a_texture_ : &texture_store.enemy_b_texture_;
	shape_.setTexture(texture, true);
	sf::Vector2f size(shape_.getTextureRect().width, shape_.getTextureRect().height);
	shape_.setSize(size);
	shape_.setOrigin(shape_.getSize() / 2.f);
	shape_.setScale(object_scale_, object_scale_);
	//setScale();
}

void 
Enemy::setInitialPosition()
{
	const sf::Vector2f offset(RandomMinusOneToOne() * 180, (RandomMinusOneToOne() + 1.0f) * 0.3f);
	shape_.setPosition(map_.width() / 2.0f, map_.height() / 2.0f);
	shape_.move(offset);
	setPosition(offset.x, offset.y);
	setRotation();
	//setScale();
}

void
Enemy::update(float dt)
{
}