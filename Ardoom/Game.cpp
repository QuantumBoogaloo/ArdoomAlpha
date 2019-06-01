#include "Game.h"

#include "Utils.h"
#include "Geometry.h"
#include "Constants.h"

#include "SectorRenderer.h"

void Game::update()
{
	const Vector2F cameraDirection { cos(camera.angle), sin(camera.angle) };

	if(this->arduboy.pressed(UP_BUTTON))
	{
		camera.position += cameraDirection;
	}

	if(this->arduboy.pressed(DOWN_BUTTON))
	{
		camera.position -= cameraDirection;
	}

	constexpr float quarterTurn = (constants::Tau<float>::value / 4);

	if(this->arduboy.pressed(LEFT_BUTTON))
	{
		const Vector2F left { cos(camera.angle - quarterTurn), sin(camera.angle - quarterTurn) };
		camera.position += left;
	}

	if(this->arduboy.pressed(RIGHT_BUTTON))
	{
		const Vector2F right { cos(camera.angle + quarterTurn), sin(camera.angle + quarterTurn) };
		camera.position += right;
	}

	if(this->arduboy.pressed(A_BUTTON))
	{
		camera.angle -= 0.1;
	}

	if(this->arduboy.pressed(B_BUTTON))
	{
		camera.angle += 0.1;
	}
}

void Game::render()
{
	SectorRenderer<Arduboy2>::render3D(this->arduboy, this->camera, this->dummySector);
	SectorRenderer<Arduboy2>::render2D(this->arduboy, this->camera, this->dummySector);
}