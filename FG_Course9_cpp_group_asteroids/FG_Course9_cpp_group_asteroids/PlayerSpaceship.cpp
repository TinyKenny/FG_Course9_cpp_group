#include "PlayerSpaceship.h"

#include "InputHandler.h"

PlayerSpaceship::PlayerSpaceship() : GameObject()
{
	position = { 100, 100 };

	std::vector<Vector2> pointsToSet;

	pointsToSet.push_back({ 0.0, 10.0 });
	pointsToSet.push_back({ 8.0, -10.0 });
	pointsToSet.push_back({ 4.0, -7.0 });
	pointsToSet.push_back({ -4.0, -7.0 });
	pointsToSet.push_back({ -8.0, -10.0 });

	setPoints(pointsToSet);
}

void PlayerSpaceship::update(double dt)
{
	if (InputHandler::getKeyHeld(SDLK_w))
	{
		// TODO accelerate
	}
	if (InputHandler::getKeyHeld(SDLK_d))
	{
		// TODO rotate clockwise
	}
	if (InputHandler::getKeyHeld(SDLK_a))
	{
		// TODO rotate counter-clockwise
	}

	if (InputHandler::getKeyHeld(SDLK_SPACE))
	{
		// TODO fire (how tho?)
	}
}
