
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "space_ship.h"
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

	// Define some constants
	const float pi = 3.14159f;
	const Map map(800, 600);
	float ballRadius = 10.f;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(map.width(), map.height(), 32), "Space Gecko",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

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

	SpaceShip space_ship(map, 0);
	

	// Initialize the pause message
	/*sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");*/

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

		// Clear the window
		window.clear(map.backgroundColor());

		// Draw the paddles and the ball
		window.draw(space_ship.shape());
		//window.draw(rightPaddle);
		//window.draw(ball);

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}
