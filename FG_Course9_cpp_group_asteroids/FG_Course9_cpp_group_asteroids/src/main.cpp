#include "Application.h"

#include <iostream>
#include <string>

/* VG checklist:
Fonts and scoring system: implemented
"UFO" that chases player: implemented
	(UFO and Asteroid use a lot of duplicated code in Application and PhysicsSystem atm)
	constantly changes its velocity so that it always moves towards the player
State machine for controlling game states: implemented
Particle system: implemented
Resource pools: implemented
Sound (option): implemented
Optimized collision detection (option): Wont be implemented
	requires spatial partitioning
*/

int main(int argc, char** argv)
{
	Window* myWindow = Window::getInstance();

	if (myWindow->wasSetUpSuccessfully())
	{
		srand((unsigned int)time(NULL));
		Application* myApp = Application::getInstace(myWindow);
		myApp->run();
		delete myApp;
	}

	delete myWindow;

	return 0;
}