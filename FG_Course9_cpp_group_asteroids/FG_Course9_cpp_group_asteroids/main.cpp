/*
#include "iostream"
#include <memory>
#include <map>
#include <algorithm>

#include "SDL.h"
*/

#include "Application.h"

#include <iostream>
#include <string>
//#include <random>



/* TODO
replay
asteroids should be destroyed when hit by bullets
asteroid respawning
player spaceship instantiate in middle of window
(nice to have) bullets should do line collision test
*/

int main(int argc, char** argv)
{
	//srand(time(NULL));

	bool playGame = true;
	while (playGame)
	{
		Application* myApp = Application::getInstace();
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

	return 0;
}