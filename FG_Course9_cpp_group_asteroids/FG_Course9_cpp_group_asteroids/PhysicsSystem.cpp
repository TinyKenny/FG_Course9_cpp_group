#include "PhysicsSystem.h"

#include "Application.h"

void PhysicsSystem::physicsUpdate(Application* app, double dt,
								  std::vector<Asteroid>& asteroids,
								  std::vector<PlayerBullet>& playerBullets,
								  PlayerSpaceship& player)
{
	for (size_t i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i].position.x += asteroids[i].velocity.x * dt;
		asteroids[i].position.y += asteroids[i].velocity.y * dt;
	}

	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].position.x += playerBullets[i].velocity.x * dt;
		playerBullets[i].position.y += playerBullets[i].velocity.y * dt;
	}

	player.position.x += player.velocity.x * dt;
	player.position.y += player.velocity.y * dt;


	// TODO loop through all asteroids to check if they get hit by any bullet or if they hit the player
	// TODO do sphere-checks (using separating axis theorem) to determine if they are close enough to be able to collide
	// if they are close enough to be able to collide, perform line intersection tests



}
