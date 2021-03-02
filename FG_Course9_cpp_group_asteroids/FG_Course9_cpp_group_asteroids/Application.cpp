#include "Application.h"

#include "InputHandler.h"

#include "Asteroid.h"

#include <chrono>
#include <iostream>
#include <string>


Application::Application()
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
	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
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
	/*
	{
		GameObject go;

		std::vector<Vector2> points;
		points.push_back({ 10, 10 });
		points.push_back({ 10, 60 });
		points.push_back({ 60, 10 });

		go.setPoints(points);
		
		gameObjects.push_back(go);
	}
	*/
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

void Application::runGameLoop()
{
	if (keepGameLoopAlive)
	{
		return;
	}

	keepGameLoopAlive = true;

	using namespace std::chrono;

	double t = 0.0; // time since start
	double dt = 1.0 / 60.0; // desired update rate
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
			std::cout << "dt: " << std::to_string(dt) << std::endl;
			for (GameObject* go : gameObjects)
			{
				go->Update(dt);
			}

			// TODO collision checks and object movement


			accumulator -= dt;
			t += dt;
		}

		renderScene();
	}
}

void Application::physicsUpdate()
{
	for (GameObject* go : gameObjects)
	{
		
	}
}

const void Application::renderScene()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (GameObject* go : gameObjects)
	{
		go->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Application::spawnAsteroids()
{
	Asteroid *ast = new Asteroid();
	gameObjects.push_back(ast);

}
