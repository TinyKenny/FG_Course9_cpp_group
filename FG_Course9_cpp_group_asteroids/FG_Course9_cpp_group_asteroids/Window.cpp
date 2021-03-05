#include "Window.h"

#include "InputHandler.h"

#include <iostream>

Window::Window()
{
	initSDL();
}

Window::~Window()
{
	InputHandler::clearAllKeys();

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

Window* Window::getInstance()
{
	return new Window();
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

void Window::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

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
