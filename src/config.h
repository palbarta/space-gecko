#pragma once

#include <SFML/Graphics.hpp>	
#include "yaml-cpp/yaml.h"
#include <string>

struct ControlConfig {
	std::vector<sf::Keyboard::Key> move_clockwise_ = { sf::Keyboard::Key::Left };
	std::vector<sf::Keyboard::Key> move_counterclockwise_ = { sf::Keyboard::Key::Right };
	std::vector<sf::Keyboard::Key> move_inwards_ = { sf::Keyboard::Key::Up };
	std::vector<sf::Keyboard::Key> move_outwards_ = { sf::Keyboard::Key::Down };
	std::vector<sf::Keyboard::Key> fire_ = { sf::Keyboard::Key::Space };
	std::vector<sf::Keyboard::Key> reset_scene_ = { sf::Keyboard::Key::R };
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
	void parseYAML(const std::string& file_path);
	std::vector<sf::Keyboard::Key> parseKeyboardControls(const std::string& action);

private:
	YAML::Node root_;
};