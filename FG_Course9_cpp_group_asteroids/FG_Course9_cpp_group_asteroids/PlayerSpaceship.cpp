#include "PlayerSpaceship.h"

#include "InputHandler.h"

//#include <math.h>

#define ROTATION_SPEED_RADIANS 0.8 * M_PI
#define ACCELERATION 40.0
//#define MAX_SPEED 50.0

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
		velocity += localToWorldMatrix.transformVector({ 0.0, (float)(ACCELERATION * dt) });
		// TODO implement speed cap
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

std::vector<Vector2> PlayerSpaceship::getPoints() const
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
