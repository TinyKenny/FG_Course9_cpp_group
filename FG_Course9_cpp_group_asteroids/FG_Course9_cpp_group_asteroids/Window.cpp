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

	if (font != nullptr)
	{
		TTF_CloseFont(font);
	}
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	if (TTF_WasInit())
	{
		TTF_Quit();
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

TTF_Font* Window::getFont()
{
	return font;
}

bool Window::wasSetUpSuccessfully()
{
	return setupSuccessful;
}

void Window::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	if (TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
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

	font = TTF_OpenFont("res/comic.ttf", 20); // TODO evaluate if font size is good
	if (font == nullptr)
	{
		std::cout << TTF_GetError() << std::endl;
		return;
	}

	setupSuccessful = true;
}
