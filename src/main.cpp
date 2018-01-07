#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <list>
#include <unordered_map>
#include <iostream>

#include "asset_store.h"
#include "config.h"
#include "debug.h"
#include "scene.h"

typedef void(Scene::*SceneAction)(float); // function pointer type
std::vector<std::pair<sf::Keyboard::Key, SceneAction>> keys_to_actions;

void ResetScene(Scene& scene)
{
	//(&scene)->~Scene();
	//new (&scene) Scene(42);
}

void
BindKeysToSceneActions()
{
	auto&& cfg = Config::getInstance().control_;
	keys_to_actions.emplace_back(cfg.move_clockwise_,			&Scene::moveSpaceShipClockwise);
	keys_to_actions.emplace_back(cfg.move_counterclockwise_, &Scene::moveSpaceShipCounterClockwise);
	keys_to_actions.emplace_back(cfg.move_inwards_,				&Scene::moveSpaceShipInwards);
	keys_to_actions.emplace_back(cfg.move_outwards_,			&Scene::moveSpaceShipOutwards);
	keys_to_actions.emplace_back(cfg.fire_,						&Scene::shootWithSpaceShip);
}

void
HandleSceneActions(Scene& scene, float dt)
{
	auto&& cfg = Config::getInstance().control_;
	for (auto&& key_to_action : keys_to_actions) {
		auto&& key = key_to_action.first;
		if (sf::Keyboard::isKeyPressed(key))
		{
			auto&& action = key_to_action.second;
			(scene.*action)(dt);
		}
	}

	if (sf::Keyboard::isKeyPressed(cfg.reset_scene_)) {
		ResetScene(scene);
	}
}

void
LogVideoModes(const std::vector<sf::VideoMode>& video_modes)
{
	for (auto&& video_mode : video_modes) {
		std::cout << video_mode.width << "x" << video_mode.height << " (" << video_mode.bitsPerPixel << "bpp)" << std::endl;
	}
}

int main()
{
	Config::getInstance().readConfigFile("settings.cfg");
	const bool loaded_resources_successfully = AssetStore::getInstance().readFiles();
	if (!loaded_resources_successfully)
		return EXIT_FAILURE;

	BindKeysToSceneActions();

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	auto&& video_modes = sf::VideoMode::getFullscreenModes();
	LogVideoModes(video_modes);
	sf::RenderWindow window(video_modes[0], "Space Gecko", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(Config::getInstance().system_.vsync_);

	Scene scene(window.getSize());
	Debug debug(scene);

	sf::Clock clock;
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}	
		}

		float dt = clock.restart().asSeconds();
		HandleSceneActions(scene, dt);
		scene.update(dt);
		debug.update(dt);
		
		// Draw
		window.clear(scene.backgroundColor());
		for (const auto* scene_object : scene.objects()) {
			window.draw(scene_object->shape());
		}
		for (const auto* debug_object : debug.objects()) {
			window.draw(*debug_object);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
