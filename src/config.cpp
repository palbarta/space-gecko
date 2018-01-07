#include "config.h"

#include "control_mapping.h"

#include "yaml-cpp/yaml.h"

#include <fstream>
#include <iostream>

YAML::Node
ParseYAML(const std::string& file_path) {
	YAML::Node doc;
	std::ifstream input_stream;
	input_stream.open(file_path);
  	try {
		doc = YAML::Load(input_stream);
   } catch (const YAML::Exception& e) {
    	std::cerr << e.what() << "\n";
  	}

	return doc;
}

void
Config::readConfigFile(const std::string& file_path)
{
	YAML::Node root = ParseYAML(file_path);
	space_ship_.radius_fraction_to_edge_of_screen_ = root["space_ship"]["radius_fraction_to_edge_of_screen"].as<float>();
	space_ship_.angular_speed_ = root["space_ship"]["angular_speed"].as<float>();
	space_ship_.radial_speed_ = root["space_ship"]["radial_speed"].as<float>();
	space_ship_.shooting_interval_in_seconds_ = sf::seconds(root["space_ship"]["shooting_interval_in_seconds"].as<float>());

	debug_.draw_bounding_boxes_ = root["debug"]["draw_bounding_boxes"].as<bool>();

	control_.move_clockwise_ = cfg_entry_to_key[root["control"]["keyboard"]["move_clockwise"].as<std::string>()];
	control_.move_counterclockwise_ = cfg_entry_to_key[root["control"]["keyboard"]["move_counterclockwise"].as<std::string>()];
	control_.move_inwards_ = cfg_entry_to_key[root["control"]["keyboard"]["move_inwards"].as<std::string>()];
	control_.move_outwards_ = cfg_entry_to_key[root["control"]["keyboard"]["move_outwards"].as<std::string>()];
	control_.fire_ = cfg_entry_to_key[root["control"]["keyboard"]["fire"].as<std::string>()];
	control_.reset_scene_ = cfg_entry_to_key[root["control"]["keyboard"]["reset_scene"].as<std::string>()];

	system_.vsync_ = root["system"]["vsync"].as<bool>();
}