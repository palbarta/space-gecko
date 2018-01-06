#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Textures {
	sf::Texture space_ship_texture_;
	sf::Texture enemy_a_texture_;
	sf::Texture enemy_b_texture_;
};

class AssetStore
{
public:
	static AssetStore& getInstance()
	{
		static AssetStore instance;
		return instance;
	}

	bool readFiles();

	const Textures& textures() const { return textures_; }

private:
	Textures textures_;
};