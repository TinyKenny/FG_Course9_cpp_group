#include "PhysicsSystem.h"
#include "Application.h"
#include <iostream>


void PhysicsSystem::physicsUpdate(Application* app, double dt,
								  std::vector<Asteroid>& asteroids,
								  std::vector<PlayerBullet>& playerBullets,
								  PlayerSpaceship& player)
{
	for (size_t i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i].position.x += asteroids[i].velocity.x * dt;
		asteroids[i].position.y += asteroids[i].velocity.y * dt;

		wrapAround(asteroids[i], app->WINDOW_WIDTH, app->WINDOW_HEIGHT);
	}

	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].position.x += playerBullets[i].velocity.x * dt;
		playerBullets[i].position.y += playerBullets[i].velocity.y * dt;

		wrapAround(playerBullets[i], app->WINDOW_WIDTH, app->WINDOW_HEIGHT);
	}

	player.position.x += player.velocity.x * dt;
	player.position.y += player.velocity.y * dt;

	wrapAround(player, app->WINDOW_WIDTH, app->WINDOW_HEIGHT);

	

	// TODO loop through all asteroids to check if they get hit by any bullet or if they hit the player
	// TODO do sphere-checks (using separating axis theorem) to determine if they are close enough to be able to collide
	// if they are close enough to be able to collide, perform line intersection tests



}
//TODO: Magic numbers, fix if-statement cluster
void PhysicsSystem::wrapAround(GameObject& go, int windowWidth, int windowHeight)
{
	if (go.position.x >= windowWidth)
	{
		std::cout << "here" << std::endl;

		go.position.x = 1;
		go.position.y = windowHeight-go.position.y;
	}

	if (go.position.x <= 0)
	{
		std::cout << "here" << std::endl;

		go.position.x = windowWidth -1;
		go.position.y = windowHeight - go.position.y;
	}

	if (go.position.y >= windowHeight)
	{
		go.position.y = 1;
		go.position.x = windowWidth - go.position.x;
	}

	if (go.position.y <= 0)
	{
		go.position.y = windowHeight-1;
		go.position.x = windowWidth - go.position.x;
	}
}
