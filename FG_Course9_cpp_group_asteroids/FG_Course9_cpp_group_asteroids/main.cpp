#include "Application.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	Window* myWindow = Window::getInstance();

	// TODO create window
	
	bool playGame = true;
	while (playGame)
	{
		Application* myApp = Application::getInstace(myWindow);
		myApp->run();
		delete myApp;

		std::cout << "Play again? y/n" << std::endl;
		bool playerHasGivenValidAnswer = false;
		while (!playerHasGivenValidAnswer)
		{

			std::string playerInput;
			std::getline(std::cin, playerInput);

			if (playerInput == "y")
			{
				playerHasGivenValidAnswer = true;
			}
			else if (playerInput == "n")
			{
				playerHasGivenValidAnswer = true;
				playGame = false;
			}
			else
			{
				std::cout << "invalid input, please input \"y\" or \"n\"" << std::endl;
			}
		}
	}

	delete myWindow;



	
	/*
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	

	int iterations = 1000000;
	std::string playerInput;
	std::getline(std::cin, playerInput);
	std::cout << "begin" << std::endl;

	for (int i = 0; i < iterations; i++)
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			std::cout << SDL_GetError() << std::endl;
		}
		if (renderer != nullptr)
		{
			SDL_DestroyRenderer(renderer);
		}
	}

	std::cout << "end" << std::endl;
	std::getline(std::cin, playerInput);

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
	if (SDL_WasInit(SDL_INIT_EVERYTHING))
	{
		SDL_Quit();
	}
	*/


	return 0;
}