#include "Application.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	srand(time(NULL));

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