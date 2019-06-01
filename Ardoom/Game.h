#pragma once

#include <Arduboy2.h>

#include "GameState.h"
#include "Entity.h"
#include "Camera.h"
#include "Sector.h"
#include "DummyData.h"

class Game
{
private:
	Arduboy2 arduboy;
	GameState gameState = GameState::Gameplay;
	Entity player;
	Camera camera { 0, { 5, 15 } };

	// Temporary sector for the sake of testing
	Sector dummySector { dummyData };

public:
	/// To be called from the main ino's setup function
	void setup()
	{
		this->arduboy.begin();
	}

	/// To be called from the main ino's loop function
	void loop()
	{
		// Don't run unless it's time for the next frame
		if(!this->arduboy.nextFrame())
			return;

		// Update the button state
		this->arduboy.pollButtons();

		// Update the game state
		this->update();

		// Clear the screen
		this->arduboy.clear();

		// Render the game
		this->render();

		// Display the frame buffer
		this->arduboy.display();
	}

private:
	/// Updates the game state
	void update();

	/// Renders the game state
	void render();
};