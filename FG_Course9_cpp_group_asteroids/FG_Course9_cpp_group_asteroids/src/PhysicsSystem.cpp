#include "PhysicsSystem.h"
#include "Application.h"

#include <math.h>

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

	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].position += playerBullets[i].velocity * dt;

		wrapAround(playerBullets[i], WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	player.position += player.velocity * dt;

	wrapAround(player, WINDOW_WIDTH, WINDOW_HEIGHT);

	
	for (size_t iUFO = 0; iUFO < UFOs.size(); ++iUFO)
	{
		bool ufoHitByBullet = false;
		
		for (size_t iPlayerBullet = 0; !ufoHitByBullet && iPlayerBullet < playerBullets.size(); ++iPlayerBullet)
		{
			Vector2 bulletPosition = playerBullets[iPlayerBullet].position; // purely for convenience and readability
			if (Vector2::sqrDistance(UFOs[iUFO].position, bulletPosition) < UFOs[iUFO].getCircleRadius() * UFOs[iUFO].getCircleRadius())
			{
				// ufo collides with bullet
				app->DestroyUFO(&UFOs[iUFO]);
				ufoHitByBullet = true;
			}
		}

		if (!ufoHitByBullet)
		{
			float distanceForCircleCollision = player.getCircleRadius() + UFOs[iUFO].getCircleRadius();

			if (Vector2::sqrDistance(player.position, UFOs[iUFO].position) < distanceForCircleCollision * distanceForCircleCollision)
			{
				if (checkShapeShapeIntersection(player.getPoints(), UFOs[iUFO].getPoints()))
				{
					// player and asteroid collides
					app->gameOver();
					break;
				}
			}
		}
	}

	for (size_t iAsteroid = 0; iAsteroid < asteroids.size(); ++iAsteroid)
	{
		bool asteroidHitByBullet = false;

		for (size_t iPlayerBullet = 0; !asteroidHitByBullet && iPlayerBullet < playerBullets.size(); ++iPlayerBullet)
		{
			Vector2 bulletPosition = playerBullets[iPlayerBullet].position; // purely for convenience and readability
			if (Vector2::sqrDistance(asteroids[iAsteroid].position, bulletPosition) < asteroids[iAsteroid].getCircleRadius() * asteroids[iAsteroid].getCircleRadius())
			{
				// asteroid collides with bullet
				app->DestroyAsteroid(&asteroids[iAsteroid]);
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
					break;
				}
			}
		}
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

