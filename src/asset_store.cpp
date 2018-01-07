#include "asset_store.h"

bool
AssetStore::readFiles()
{
	// Load the sounds used in the game
	/*sf::SoundBuffer ballSoundBuffer;
	if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
		return false;
	sf::Sound ballSound(ballSoundBuffer);*/

	// Load textures
	if (!textures_.space_ship_texture_.loadFromFile("resources/space_ship.png"))
		return false;
	if (!textures_.enemy_a_texture_.loadFromFile("resources/enemy_a.png"))
		return false;
	if (!textures_.enemy_b_texture_.loadFromFile("resources/enemy_b.png"))
		return false;
	
	// Load the text font
	//sf::Font font;
	//if (!font.loadFromFile("resources/sansation.ttf"))
	//	return false;

	return true;
}