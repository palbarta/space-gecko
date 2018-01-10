#pragma once

#include "scene.h"

#include <memory>

class Debug;
class Scene;
namespace sf {
	class RenderWindow;
}

class Game
{
public:
	Game();
	~Game();
	bool init();
	void run();
private:
	void handleSceneActions(float dt);

private:
	std::unique_ptr<Scene> scene_ { nullptr };
	std::unique_ptr<Debug> debug_ { nullptr };
	std::unique_ptr<sf::RenderWindow> window_ { nullptr };
};