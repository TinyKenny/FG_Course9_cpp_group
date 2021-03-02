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

	// TODO loop through all asteroids to check if they get hit by any bullet or if they hit the player
}
