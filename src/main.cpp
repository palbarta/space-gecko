
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "bullet.h"
#include "space_ship.h"
#include "star.h"
#include "map.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	std::vector<SceneObject*> scene_objects;
	// Define some constants
	const float pi = 3.14159f;
	
	float ballRadius = 10.f;

	auto&& video_modes = sf::VideoMode::getFullscreenModes();

	// Create the window of the application
	sf::RenderWindow window(video_modes[0], "Space Gecko", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	sf::Vector2u window_size = window.getSize();
	const Map map(window_size.x, window_size.y);

	// Load the sounds used in the game
	sf::SoundBuffer ballSoundBuffer;
	if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
		return EXIT_FAILURE;
	sf::Sound ballSound(ballSoundBuffer);

	// Create the ball
	sf::CircleShape ball;
	ball.setRadius(ballRadius - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	
	const int number_of_stars = 100;
	for (int i=0; i < number_of_stars; ++i) {
		scene_objects.push_back(new Star(map));
	}

	SpaceShip space_ship(map, 0);
	scene_objects.push_back(&space_ship);

	// Initialize the pause message
	sf::Text debug_message;
	debug_message.setFont(font);
	debug_message.setCharacterSize(30);
	debug_message.setFillColor(sf::Color::White);

	// Define the paddles properties
	sf::Clock shootingTimer;
	const sf::Time shootingTime = sf::seconds(0.1f);
	bool ableToShoot = true;
	const float paddleSpeed = 400.f;
	float rightPaddleSpeed = 0.f;
	const float ballSpeed = 400.f;
	float ballAngle = 0.f; // to be changed later

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

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				scene_objects.push_back(new Bullet(map, space_ship));
			}
		}

		float dt = clock.restart().asSeconds();

		// Move the player's paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			space_ship.moveLeft(dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			space_ship.moveRight(dt);
		}

		// Update the computer's paddle direction according to the ball position
		if (shootingTimer.getElapsedTime() > shootingTime)
		{
			shootingTimer.restart();
			ableToShoot = true;
		}

		/*debug_message.setPosition(space_ship.shape().getPosition());
		std::stringstream ss;
		auto&& x = space_ship.shape().getPosition().x - map.midPoint().x;
		auto&& y = space_ship.shape().getPosition().y - map.midPoint().y;
		ss << "x:" << x << ", y:" << y << ", deg:" << space_ship.angle();
		debug_message.setString(ss.str());*/
		// Move the ball
		//float factor = ballSpeed * deltaTime;
		//ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

		// Check the collisions between the ball and the paddles
		// Left Paddle
		/*if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
			ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
			ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
			ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
		{
			if (ball.getPosition().y > leftPaddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			ballSound.play();
			ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
		}

		// Right Paddle
		if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
			ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
			ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
			ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
		{
			if (ball.getPosition().y > rightPaddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			ballSound.play();
			ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
		}*/

		// Draw
		window.clear(map.backgroundColor());
		for (auto&& scene_object : scene_objects) {
			scene_object->update(dt);
			window.draw(scene_object->shape());	
		}
		window.draw(debug_message);
		window.display();
	}

	return EXIT_SUCCESS;
}
