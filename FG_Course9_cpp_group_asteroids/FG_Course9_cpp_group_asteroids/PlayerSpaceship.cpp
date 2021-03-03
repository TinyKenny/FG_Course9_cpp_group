#include "PlayerSpaceship.h"

#include "InputHandler.h"

//#include <math.h>

#define ROTATION_SPEED_RADIANS 0.8 * M_PI

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

	localToWorldMatrix.rotateByRadians(M_PI);
}

void PlayerSpaceship::update(double dt)
{
	if (InputHandler::getKeyHeld(SDLK_w))
	{
		// TODO accelerate
	}
	if (InputHandler::getKeyHeld(SDLK_d))
	{
		localToWorldMatrix.rotateByRadians(ROTATION_SPEED_RADIANS * dt);
	}
	if (InputHandler::getKeyHeld(SDLK_a))
	{
		localToWorldMatrix.rotateByRadians(-ROTATION_SPEED_RADIANS * dt);
	}

	if (InputHandler::getKeyHeld(SDLK_SPACE))
	{
		// TODO fire (how tho?)
	}
}

const std::vector<Vector2> PlayerSpaceship::getPoints()
{
	std::vector<Vector2> worldPoints;
	worldPoints.reserve(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		Vector2 worldSpacePoint = localToWorldMatrix.transformVector(points[i]);
		worldSpacePoint.x += position.x;
		worldSpacePoint.y += position.y;
		worldPoints.push_back(worldSpacePoint);
	}

	return worldPoints;
}
