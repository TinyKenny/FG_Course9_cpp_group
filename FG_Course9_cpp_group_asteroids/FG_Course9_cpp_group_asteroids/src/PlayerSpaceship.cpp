#include "PlayerSpaceship.h"
#include "InputHandler.h"
#include "PlayerBullet.h"
#include "Application.h"
#include <chrono>
//#include <math.h>

#define ROTATION_SPEED_RADIANS 0.8 * M_PI
#define ACCELERATION 40.0
//#define MAX_SPEED 50.0

using namespace std::chrono;

PlayerSpaceship::PlayerSpaceship(Application *application) : GameObject()
{

	std::vector<Vector2> pointsToSet;

	pointsToSet.push_back({ 0.0, 10.0 });
	pointsToSet.push_back({ 8.0, -10.0 });
	pointsToSet.push_back({ 4.0, -7.0 });
	pointsToSet.push_back({ -4.0, -7.0 });
	pointsToSet.push_back({ -8.0, -10.0 });

	setPoints(pointsToSet);

	this->application = application;

	reset();
}

void PlayerSpaceship::reset()
{
	position = { (float)(WINDOW_WIDTH / 2), (float)(WINDOW_HEIGHT / 2) };
	localToWorldMatrix = Matrix2x2();
	localToWorldMatrix.rotateByRadians(M_PI);
	velocity = { 0.0, 0.0 };
}

void PlayerSpaceship::update(double dt)
{
	if (fireCooldownTimer > 0)
	{
		fireCooldownTimer -= dt;
	}

	if (InputHandler::getKeyHeld(SDLK_w))
	{
		velocity += localToWorldMatrix.transformVector({ 0.0, (float)(ACCELERATION * dt) });
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
		if (fireCooldownTimer > 0)
		{
			return;
		}

		fireCooldownTimer += fireRate;

		application->spawnBullet(localToWorldMatrix.transformVector({ 0.0, 1.0 }), position);
	}

}

std::vector<Vector2> PlayerSpaceship::getPoints() const
{
	std::vector<Vector2> worldPoints;
	worldPoints.reserve(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		Vector2 worldSpacePoint = localToWorldMatrix.transformVector(points[i]);
		worldSpacePoint.x += position.x;
		worldSpacePoint.y += position.y;
		worldPoints.push_back(worldSpacePoint);
	}

	return worldPoints;
}
