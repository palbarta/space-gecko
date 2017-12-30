#include "config.h"

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
	space_ship_.speed_ = root["space_ship"]["speed"].as<float>();
	space_ship_.shooting_interval_in_seconds_ = sf::seconds(root["space_ship"]["shooting_interval_in_seconds"].as<float>());
}