#pragma once

struct Settings
{
public:
	static Settings& getInstance() { return instance_; }

	float space_ship_radius_ratio_to_edge_of_screen = 0.8f;

private:
	Settings() {};
	static Settings instance_;
};