#include "Application.h"

#include "InputHandler.h"
#include "PhysicsSystem.h"

#include <chrono>
#include <iostream>
#include <string>


Application::Application() : player(this)
{
	initSDL();
}

void Application::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	// TODO not have hard-coded name and window size
	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
}


Application::~Application()
{
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
	if (SDL_WasInit(SDL_INIT_EVERYTHING))
	{
		SDL_Quit();
	}
}

Application* Application::getInstace()
{
	return new Application();
}

void Application::run()
{
	spawnAsteroids();

	if (!keepGameLoopAlive && SDL_WasInit(SDL_INIT_EVERYTHING) && window != nullptr && renderer != nullptr)
	{
		runGameLoop();
	}
}

void Application::quit()
{
	keepGameLoopAlive = false;
}

void Application::gameOver()
{
	if (keepGameLoopAlive) // prevent multiple game-over messages being printed by colliding with multiple asteroids in the same update
	{
		std::cout << std::endl << "You got hit by an asteroid, game over!" << std::endl;
	}
	quit();
}

void Application::spawnBullet(Vector2 direction, Vector2 startPosition)
{
	PlayerBullet bullet(direction, startPosition);
	playerBullets.push_back(bullet);
}

void Application::runGameLoop()
{
	if (keepGameLoopAlive)
	{
		return;
	}

	keepGameLoopAlive = true;

	using namespace std::chrono;

	double t = 0.0; // time since start
	dt = 1.0 / 60.0; // desired update rate
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();

	while (keepGameLoopAlive)
	{
		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = (duration_cast<duration<double>>(newTime - currentTime)).count();
		currentTime = newTime;
		accumulator += frameTime;

		InputHandler::updateInputs(this);

		while (accumulator >= dt)
		{
			player.update(dt);
			updateBullets();

			PhysicsSystem::physicsUpdate(this, dt, asteroids, playerBullets, player);

			accumulator -= dt;
			t += dt;
		}


		renderScene();
	}
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
	asteroids.push_back(Asteroid(window));
	asteroids.push_back(Asteroid(window));
	asteroids.push_back(Asteroid(window));
	asteroids.push_back(Asteroid(window));
}


void Application::updateBullets()
{
	for (int i = 0; i < playerBullets.size(); i++)
	{
		bool isAlive = playerBullets[i].updateLifetime(dt);

		if (!isAlive)
		{
			playerBullets.erase(playerBullets.begin()+i);
			i--;
		}
	}
}

void Application::DestroyAsteroid(Asteroid* asteroid)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		//std::cout << asteroid << std::endl;
		//std::cout << (&asteroids[i]) << std::endl;

		if (&asteroids[i] == asteroid)
		{
			asteroids.erase(asteroids.begin() + i);
			i--;
		}
	}
}
