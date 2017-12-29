#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Debug
{
public:
	Debug();
	void update(float dt);
	const std::list<sf::Drawable*>& debugGraphics() const { return graphics_; }

private:
	std::list<sf::Drawable*> graphics_;
};