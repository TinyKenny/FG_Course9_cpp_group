#include "Application.h"

#include <chrono>
#include <iostream>
#include <string>


Application::Application()
{

}

Application* Application::getInstace()
{
	return new Application();
}

void Application::run()
{
	// TODO init SDL
	// TODO make SDL window
	// TODO make SDL renderer

	runGameLoop();

	// TODO destroy SDL renderer
	// TODO destroy SDL window
	// TODO SDL_Quit();
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

		// TODO handle input!

		while (accumulator >= dt)
		{
			std::cout << "dt: " << std::to_string(dt) << std::endl;
			for (GameObject go : gameObjects)
			{
				go.Update(dt);
			}
			// TODO collision checks and movement


			accumulator -= dt;
			t += dt;
		}

		// TODO render
	}

}
