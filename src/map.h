#pragma once
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map(sf::Vector2u window_size);

	int width() const { return width_; }
	int height() const { return height_; }
	const sf::Vector2f& midPoint() const { return mid_point_; }
	const sf::Color& backgroundColor() const { return color_; }

private:
	const int width_;
	const int height_;
	const sf::Vector2f mid_point_;
	sf::Color color_{ 0, 0, 0 };
};