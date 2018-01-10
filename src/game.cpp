#include "game.h"

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

void
BindKeysToSceneActions()
{
	keys_to_actions.clear();
	auto&& cfg = Config::getInstance().control_;
	keys_to_actions.emplace_back(cfg.move_clockwise_,			&Scene::moveSpaceShipClockwise);
	keys_to_actions.emplace_back(cfg.move_counterclockwise_, 	&Scene::moveSpaceShipCounterClockwise);
	keys_to_actions.emplace_back(cfg.move_inwards_,				&Scene::moveSpaceShipInwards);
	keys_to_actions.emplace_back(cfg.move_outwards_,			&Scene::moveSpaceShipOutwards);
	keys_to_actions.emplace_back(cfg.fire_,						&Scene::shootWithSpaceShip);
}


void
LogVideoModes(const std::vector<sf::VideoMode>& video_modes)
{
	for (auto&& video_mode : video_modes) {
		std::cout << video_mode.width << "x" << video_mode.height << " (" << video_mode.bitsPerPixel << "bpp)" << std::endl;
	}
}

Game::Game()
{
	auto&& video_modes = sf::VideoMode::getFullscreenModes();
	//LogVideoModes(video_modes);
	window_ = std::make_unique<sf::RenderWindow>(video_modes[0], "Space Gecko", sf::Style::Fullscreen);
}

Game::~Game()
{
}

bool
Game::init()
{
	Config::getInstance().readConfigFile("settings.cfg");
	const bool loaded_resources_successfully = AssetStore::getInstance().readFiles();
	if (!loaded_resources_successfully)
		return false;

	BindKeysToSceneActions();
	
	window_->setVerticalSyncEnabled(Config::getInstance().system_.vsync_);

	scene_ = std::make_unique<Scene>(window_->getSize());
	debug_ = std::make_unique<Debug>(*scene_);

	return true;
}

void 
Game::run()
{
	sf::Clock clock;
	while (window_->isOpen())
	{
		// Handle events
		sf::Event event;
		while (window_->pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window_->close();
				break;
			}	
			
			auto&& cfg = Config::getInstance().control_;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == cfg.reset_scene_)) {
				init();
			}
		}

		float dt = clock.restart().asSeconds();
		handleSceneActions(dt);
		scene_->update(dt);
		debug_->update(dt);
		
		// Draw
		window_->clear(scene_->backgroundColor());
		for (const auto* scene_object : scene_->objects()) {
			window_->draw(scene_object->shape());
		}
		for (const auto* debug_object : debug_->objects()) {
			window_->draw(*debug_object);
		}

		window_->display();
	}
}

void
Game::handleSceneActions(float dt)
{
	auto&& cfg = Config::getInstance().control_;
	for (auto&& key_to_action : keys_to_actions) {
		auto&& key = key_to_action.first;
		if (sf::Keyboard::isKeyPressed(key))
		{
			auto&& action = key_to_action.second;
			((*scene_).*action)(dt);
		}
	}

	
}