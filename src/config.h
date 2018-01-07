#pragma once

#include <string>
#include <SFML/Graphics.hpp>	

struct ControlConfig {
	sf::Keyboard::Key move_clockwise_ = sf::Keyboard::Key::Left;
	sf::Keyboard::Key move_counterclockwise_ = sf::Keyboard::Key::Right;
	sf::Keyboard::Key move_inwards_ = sf::Keyboard::Key::Up;
	sf::Keyboard::Key move_outwards_ = sf::Keyboard::Key::Down;
	sf::Keyboard::Key fire_ = sf::Keyboard::Key::Space;
	sf::Keyboard::Key reset_scene_ = sf::Keyboard::Key::R;
};

struct DebugConfig {
	bool draw_bounding_boxes_ = false;
};

struct SpaceShipConfig {
	float radius_fraction_to_edge_of_screen_ = 0.8f;
	float angular_speed_ = 3.0f;
	float radial_speed_ = 10.0f;
	sf::Time shooting_interval_in_seconds_ = sf::seconds(0.2f);
};

struct SystemConfig {
	bool vsync_ = false;
};

struct Config
{
	static Config& getInstance() 
	{ 
		static Config instance;
		return instance;
	}

	void readConfigFile(const std::string& file_path);

	ControlConfig control_;
	DebugConfig debug_;
	SpaceShipConfig space_ship_;
	SystemConfig system_;
	
private:
	Config() {};
};