#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f RandomDirection();
float RandomMinusOneToOne();

template<typename T>
bool
EqualsAnyOf(std::vector<T> list, T value) {
	return std::any_of(list.begin(), list.end(), [&](T& one_value_in_list) {return one_value_in_list == value; });
}