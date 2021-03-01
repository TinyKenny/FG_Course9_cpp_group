#include "Application.h"

#include "InputHandler.h"

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
	window = new Window();

	/*
	std::vector<Vector2> points;
	points.push_back({ 10.0, 10.0 });
	points.push_back({ 10.0, 60.0 });
	points.push_back({ 60.0, 10.0 });

	GameObject myGO;
	myGO.setPoints(points);

	gameObjects.push_back(myGO);
	*/
	// TODO populate gameobject list

	if (window->initializedSuccessfully())
	{
		runGameLoop();
	}

	delete window;

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
			for (GameObject go : gameObjects)
			{
				go.Update(dt);
			}

			// TODO collision checks and object movement

			accumulator -= dt;
			t += dt;
		}

		window->render(gameObjects);
	}
}
