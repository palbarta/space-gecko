#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <list>
#include <unordered_map>

#include "config.h"
#include "scene.h"

typedef void(Scene::*SceneAction)(float); // function pointer type
std::vector<std::pair<sf::Keyboard::Key, SceneAction>> keys_to_actions;

void
BindKeysToSceneActions()
{
	keys_to_actions.emplace_back(sf::Keyboard::Left,  &Scene::moveSpaceShipClockwise);
	keys_to_actions.emplace_back(sf::Keyboard::Right, &Scene::moveSpaceShipCounterClockwise);
	keys_to_actions.emplace_back(sf::Keyboard::Space, &Scene::shootWithSpaceShip);
}

void
HandleSceneActions(Scene& scene, float dt)
{
	for (auto&& key_to_action : keys_to_actions) {
		auto&& key = key_to_action.first;
		if (sf::Keyboard::isKeyPressed(key))
		{
			auto&& action = key_to_action.second;
			(scene.*action)(dt);
		}
	}
}

int main()
{
	Config::getInstance().readConfigFile("settings.cfg");
	BindKeysToSceneActions();

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	auto&& video_modes = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow window(video_modes[0], "Space Gecko", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	Scene scene(window.getSize());

	// Load the sounds used in the game
	sf::SoundBuffer ballSoundBuffer;
	if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
		return EXIT_FAILURE;
	sf::Sound ballSound(ballSoundBuffer);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

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
		
		// Draw
		window.clear(scene.backgroundColor());
		for (const auto* scene_object : scene.objects()) {
			window.draw(scene_object->shape());
		}
		//window.draw(debug_message);
		window.display();
	}

	return EXIT_SUCCESS;
}
