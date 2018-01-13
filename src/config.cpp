#include "config.h"

#include "control_mapping.h"

#include <fstream>
#include <iostream>

void
Config::parseYAML(const std::string& file_path) {
	YAML::Node doc;
	std::ifstream input_stream;
	input_stream.open(file_path);
  	try {
		root_ = YAML::Load(input_stream);
    } catch (const YAML::Exception& e) {
    	std::cerr << e.what() << "\n";
  	}
}

std::vector<sf::Keyboard::Key>
Config::parseKeyboardControls(const std::string& action)
{
	auto&& controls = root_["control"]["keyboard"];
	std::vector<sf::Keyboard::Key> key_list;
	for (auto&& key_str : controls[action].as<std::vector<std::string>>()) {
		key_list.push_back(cfg_entry_to_key[key_str]);
	}
	return key_list;
}

void
Config::readConfigFile(const std::string& file_path)
{
	try {
		parseYAML(file_path);
		space_ship_.radius_fraction_to_edge_of_screen_ = root_["space_ship"]["radius_fraction_to_edge_of_screen"].as<float>();
		space_ship_.angular_speed_ = root_["space_ship"]["angular_speed"].as<float>();
		space_ship_.radial_speed_ = root_["space_ship"]["radial_speed"].as<float>();
		space_ship_.shooting_interval_in_seconds_ = sf::seconds(root_["space_ship"]["shooting_interval_in_seconds"].as<float>());

		debug_.draw_bounding_boxes_ = root_["debug"]["draw_bounding_boxes"].as<bool>();

		control_.move_clockwise_ = parseKeyboardControls("move_clockwise");
		control_.move_counterclockwise_ = parseKeyboardControls("move_counterclockwise");
		control_.move_inwards_ = parseKeyboardControls("move_inwards");
		control_.move_outwards_ = parseKeyboardControls("move_outwards");
		control_.fire_ = parseKeyboardControls("fire");
		control_.reset_scene_ = parseKeyboardControls("reset_scene");

		system_.vsync_ = root_["system"]["vsync"].as<bool>();
	}
	catch (const YAML::BadConversion& e) {
    	std::cerr << e.what() <<  "\n";
  	}
}