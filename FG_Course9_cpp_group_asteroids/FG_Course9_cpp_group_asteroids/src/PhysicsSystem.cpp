#include "PhysicsSystem.h"
#include "Application.h"

#include <math.h>

#include <iostream>

#define MINIMUM_DENOMINATOR 0.00001f

void PhysicsSystem::physicsUpdate(Application* app, double dt,
								  std::vector<UFO>& UFOs,
								  std::vector<Asteroid>& asteroids,
								  std::vector<PlayerBullet>& playerBullets,
								  PlayerSpaceship& player)
{


	for (size_t i = 0; i < UFOs.size(); ++i)
	{
		UFOs[i].position += UFOs[i].velocity * dt;
		wrapAround(UFOs[i], WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	for (size_t i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i].position += asteroids[i].velocity * dt;

		wrapAround(asteroids[i], WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	player.position += player.velocity * dt;

	wrapAround(player, WINDOW_WIDTH, WINDOW_HEIGHT);

	// TODO collision detection with UFOs

	for (size_t iAsteroid = 0; iAsteroid < asteroids.size(); ++iAsteroid)
	{
		bool asteroidHitByBullet = false;
		
		for (size_t iPlayerBullet = 0; !asteroidHitByBullet && iPlayerBullet < playerBullets.size(); ++iPlayerBullet)
		{
			Vector2 bulletPosition = playerBullets[iPlayerBullet].position; // purely for convenience and readability
			if (Vector2::sqrDistance(asteroids[iAsteroid].position, bulletPosition) < asteroids[iAsteroid].getCircleRadius() * asteroids[iAsteroid].getCircleRadius())
			{
				// asteroid collides with bullet
				/*
				if (checkLineSegmentShapeIntersection(asteroids[iAsteroid].getPoints(), bulletPosition, bulletPosition + playerBullets[iPlayerBullet].velocity * dt))
				{
				}
				*/
					asteroids[iAsteroid].DestroyAsteroid(app); // contains logic for splitting/destroying the asteroid in question
					asteroidHitByBullet = true;
			}
		}

		if (!asteroidHitByBullet)
		{
			float distanceForCircleCollision = player.getCircleRadius() + asteroids[iAsteroid].getCircleRadius();

			if (Vector2::sqrDistance(player.position, asteroids[iAsteroid].position) < distanceForCircleCollision * distanceForCircleCollision)
			{
				if (checkShapeShapeIntersection(player.getPoints(), asteroids[iAsteroid].getPoints()))
				{
					// player and asteroid collides
					app->gameOver();
					// break;
				}
			}
		}
	}

	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].position += playerBullets[i].velocity * dt;

		wrapAround(playerBullets[i], WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

void PhysicsSystem::wrapAround(GameObject& go, int windowWidth, int windowHeight)
{
	if (go.position.x >= windowWidth)
	{
		go.position.x -= windowWidth;
	}
	else if (go.position.x < 0)
	{
		go.position.x += windowWidth;
	}

	if (go.position.y >= windowHeight)
	{
		go.position.y -= windowHeight;
	}
	else if (go.position.y < 0)
	{
		go.position.y += windowHeight;
	}
}

bool PhysicsSystem::checkShapeShapeIntersection(const std::vector<Vector2>& shapeOnePoints, const std::vector<Vector2>& shapeTwoPoints)
{
	for (size_t iShapeOne = 0; iShapeOne < shapeOnePoints.size(); ++iShapeOne)
	{
		Vector2 lineOneStart = shapeOnePoints[iShapeOne];
		Vector2 lineOneEnd = shapeOnePoints[(iShapeOne + 1) % shapeOnePoints.size()];

		Vector2 lineOneDirection = lineOneEnd - lineOneStart;

		float lowestDenominator = 1000000.0f;

		for (size_t iShapeTwo = 0; iShapeTwo < shapeTwoPoints.size(); ++iShapeTwo)
		{
			Vector2 lineTwoStart = shapeTwoPoints[iShapeTwo];
			Vector2 lineTwoEnd = shapeTwoPoints[(iShapeTwo + 1) % shapeTwoPoints.size()];

			Vector2 lineTwoDirection = lineTwoEnd - lineTwoStart;

			float denominator = lineOneDirection.x * lineTwoDirection.y - lineTwoDirection.x * lineOneDirection.y;

			if (std::abs(denominator) < MINIMUM_DENOMINATOR)
			{
				continue;
			}

			Vector2 oneStartToTwoStart = lineTwoStart - lineOneStart;

			float tOne = (oneStartToTwoStart.x * lineTwoDirection.y - lineTwoDirection.x * oneStartToTwoStart.y) / denominator;
			if (tOne < 0 || tOne > 1)
			{
				continue;
			}
			float tTwo = (oneStartToTwoStart.x * lineOneDirection.y - lineOneDirection.x * oneStartToTwoStart.y) / denominator;

			if (tTwo >= 0 && tTwo <= 1)
			{
				return true;
			}
		}
	}

	return false;
}

bool PhysicsSystem::checkLineSegmentShapeIntersection(const std::vector<Vector2>& shapePoints, const Vector2 lineSegmentStart, const Vector2 lineSegmentEnd)
{
	Vector2 lineSegmentDirection = lineSegmentEnd - lineSegmentStart;

	for (size_t iShape = 0; iShape < shapePoints.size(); ++iShape)
	{
		Vector2 shapeLineStart = shapePoints[iShape];
		Vector2 shapeLineEnd = shapePoints[(iShape + 1) % shapePoints.size()];

		Vector2 shapeLineDirection = shapeLineEnd - shapeLineStart;

		float denominator = shapeLineDirection.x * lineSegmentDirection.y - lineSegmentDirection.x * shapeLineDirection.y;

		if (std::abs(denominator) < MINIMUM_DENOMINATOR)
		{
			continue;
		}

		Vector2 shapeLineStartToLineSegmentStart = lineSegmentStart - shapeLineStart;

		float tOne = (shapeLineStartToLineSegmentStart.x * lineSegmentDirection.y - lineSegmentDirection.x * shapeLineStartToLineSegmentStart.y) / denominator;
		if (tOne < 0 || tOne > 1)
		{
			continue;
		}

		float tTwo = (shapeLineStartToLineSegmentStart.x * shapeLineDirection.y - shapeLineDirection.x * shapeLineStartToLineSegmentStart.y) / denominator;
		if (tTwo >= 0 && tTwo <= 1)
		{
			return true;
		}
	}

	return false;
}

