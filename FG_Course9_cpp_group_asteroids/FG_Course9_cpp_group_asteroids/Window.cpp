#include "Window.h"



#include <iostream>

Window::Window()
{
	initialize();
}

Window::~Window()
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

bool Window::initializedSuccessfully()
{
	return initSuccessful;
}

void Window::testRender()
{
	SDL_Rect myRect;
	myRect.x = 50;
	myRect.y = 50;
	myRect.w = 100;
	myRect.h = 100;

	SDL_Rect mySecondRect;
	mySecondRect.x = 200;
	mySecondRect.y = 200;
	mySecondRect.w = 100;
	mySecondRect.h = 100;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &myRect);
	SDL_RenderDrawRect(renderer, &mySecondRect);

	SDL_RenderPresent(renderer);
}

void Window::render(const std::vector<GameObject>& gameObjects)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (GameObject go : gameObjects)
	{
		std::vector<Vector2> points = go.getPoints();
		int pointCount = points.size();
		for (int i = 0; i < pointCount; ++i)
		{
			SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[(i + 1) % pointCount].x, points[(i + 1) % pointCount].y);
		}
	}

	SDL_RenderPresent(renderer);
}

void Window::initialize()
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

	initSuccessful = true;
}
