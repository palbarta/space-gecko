#pragma once

#include <string>
#include <SFML/Graphics.hpp>	

struct SpaceShipConfig {
	float radius_fraction_to_edge_of_screen_ = 0.8f;
	float speed_ = 3.0f;
	sf::Time shooting_interval_in_seconds_ = sf::seconds(0.2f);
};

struct DebugConfig {
	bool draw_bounding_boxes_ = false;
};

struct Config
{
	static Config& getInstance() 
	{ 
		static Config instance;
		return instance;
	}

	void readConfigFile(const std::string& file_path);

	SpaceShipConfig space_ship_;
	DebugConfig debug_;

private:
	Config() {};
};