#include "Application.h"

#include "InputHandler.h"
#include "PhysicsSystem.h"

#include <chrono>
#include <iostream>
#include <string>



Application::Application(Window* window) : player(this), dt(1.0 / 60.0)
{
	myWindow = window;
	renderer = window->getRenderer();
}


Application::~Application()
{

}

Application* Application::getInstace(Window* window)
{
	if (window == nullptr)
	{
		std::cout << "instantiation of application with nullptr window attempted, returning nullptr" << std::endl;
		return nullptr;
	}
	return new Application(window);
}

void Application::run()
{
	if (!keepApplicationAlive)
	{
		keepApplicationAlive = true;

		while (keepApplicationAlive)
		{
			// cyclical statemachine
			gameplayState();

			gameOverState(); // can set keepApplicationAlive to false, depending on player input
		}
	}
}

void Application::quit()
{
	keepApplicationAlive = false;
	keepGameLoopAlive = false;
}

void Application::gameOver()
{
	keepGameLoopAlive = false;
}

void Application::spawnBullet(Vector2 direction, Vector2 startPosition)
{
	PlayerBullet bullet(direction, startPosition);
	playerBullets.push_back(bullet);
}

void Application::DestroyAsteroid(Asteroid* asteroid)
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		if (&asteroids[i] == asteroid)
		{
			asteroids.erase(asteroids.begin() + i);
		}
	}

	if (asteroids.size() == 0)
	{
		spawnAsteroids();
	}
}

void Application::gameplayState()
{
	if (keepGameLoopAlive)
	{
		return;
	}

	keepGameLoopAlive = true;

	using namespace std::chrono;

	double t = 0.0; // time since start
	//dt = 1.0 / 60.0; // desired update rate
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();
	
	player.resetPositionAndRotation();
	spawnAsteroids();

	while (keepGameLoopAlive)
	{
		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = (duration_cast<duration<double>>(newTime - currentTime)).count();
		currentTime = newTime;
		accumulator += frameTime;


		while (accumulator >= dt)
		{
			InputHandler::updateInputs(this);

			player.update(dt);
			updateBullets();

			PhysicsSystem::physicsUpdate(this, dt, asteroids, playerBullets, player);

			accumulator -= dt;
			t += dt;
		}

		renderScene();
	}

	asteroids.clear();
	playerBullets.clear();
}


const void Application::renderScene()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (Asteroid& asteroid : asteroids)
	{
		asteroid.draw(renderer);
	}

	for (PlayerBullet& bullet : playerBullets)
	{
		bullet.draw(renderer);
	}
	
	player.draw(renderer);

	SDL_RenderPresent(renderer);
}

void Application::spawnAsteroids()
{
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
}

void Application::updateBullets()
{
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		bool isAlive = playerBullets[i].updateLifetime(dt);

		if (!isAlive)
		{
			playerBullets.erase(playerBullets.begin()+i);
			i--;
		}
	}
}

void Application::gameOverState()
{
	if (!keepApplicationAlive)
	{
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// TODO display game over text
	std::cout << std::endl << "You got hit by an asteroid, game over!" << std::endl;
	std::cout << "press enter to play again or press escape to exit" << std::endl;

	SDL_RenderPresent(renderer);

	// TODO listen for player input

	while (keepApplicationAlive)
	{
		InputHandler::updateInputs(this);

		if (InputHandler::getKeyDown(SDLK_RETURN) || InputHandler::getKeyDown(SDLK_KP_ENTER))
		{
			return;
		}
		else if (InputHandler::getKeyDown(SDLK_ESCAPE))
		{
			keepApplicationAlive = false;
		}
	}
}