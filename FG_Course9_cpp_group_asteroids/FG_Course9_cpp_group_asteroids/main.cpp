/*
#include "iostream"
#include <memory>
#include <map>
#include <algorithm>

#include "SDL.h"
*/

#include "Application.h"

int main(int argc, char** argv)
{
	/*
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Window* window = SDL_CreateWindow("Match 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	*/

	Application* myApp = Application::getInstace();
	myApp->run();

	return 0;
}