#include "PhysicsSystem.h"
#include "Application.h"
#include <iostream>


void PhysicsSystem::physicsUpdate(Application* app, double dt,
								  std::vector<Asteroid>& asteroids,
								  std::vector<PlayerBullet>& playerBullets,
								  PlayerSpaceship& player)
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].position += asteroids[i].velocity * dt;

		wrapAround(asteroids[i], app->WINDOW_WIDTH, app->WINDOW_HEIGHT);
	}

	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i].position += playerBullets[i].velocity * dt;

		wrapAround(playerBullets[i], app->WINDOW_WIDTH, app->WINDOW_HEIGHT);
	}

	player.position += player.velocity * dt;

	wrapAround(player, app->WINDOW_WIDTH, app->WINDOW_HEIGHT);


	
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		bool asteroidHitByBullet = false;
		// TODO check for collision with player bullets
		for (size_t iPlayerBullet = 0; !asteroidHitByBullet && iPlayerBullet < playerBullets.size(); i++)
		{
			if (Vector2::sqrDistance(asteroids[i].position, playerBullets[iPlayerBullet].position) < asteroids[i].getCircleRadius() * asteroids[i].getCircleRadius())
			{
				// TODO asteroid collides with bullet
				asteroids[i].DestroyAsteroid(app); // contains logic for splitting/destroying the asteroid in question
				asteroidHitByBullet = true;
			}
		}

		if (!asteroidHitByBullet)
		{

			float distanceForCircleCollision = player.getCircleRadius() + asteroids[i].getCircleRadius();

			if (Vector2::sqrDistance(player.position, asteroids[i].position) < distanceForCircleCollision * distanceForCircleCollision)
			{
				// collision possible, check line intersection
				app->gameOver();
				break;
			}
		}
	}

	// TODO loop through all asteroids to check if they get hit by any bullet or if they hit the player
	// TODO do sphere-checks (using separating axis theorem) to determine if they are close enough to be able to collide
	// if they are close enough to be able to collide, perform line intersection tests



}
//TODO: Magic numbers, fix if-statement cluster
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
		go.position.y -= windowWidth;
	}
	else if (go.position.y < 0)
	{
		go.position.y += windowHeight;
	}
}

/*
bool PhysicsSystem::checkLineShapeIntersection(std::vector<Vector2>& shapeOnePoints, std::vector<Vector2>& shapeTwoPoints)
{
	for (size_t iShapeOne = 0; iShapeOne < shapeOnePoints.size(); iShapeOne++)
	{
		Vector2 shapeOnePointOne = shapeOnePoints[iShapeOne];
		Vector2 shapeOnePointTwo = shapeOnePoints[(iShapeOne + 1) % shapeOnePoints.size()];

		for (size_t iShapeTwo = 0; iShapeTwo < shapeTwoPoints.size(); iShapeTwo++)
		{
			
		}
	}

	return true;
}
*/

