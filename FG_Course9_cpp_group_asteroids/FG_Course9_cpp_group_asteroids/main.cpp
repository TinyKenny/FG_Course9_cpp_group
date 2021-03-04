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



/* TODO
replay
asteroids should be destroyed when hit by bullets
actual game over when player is hit by an asteroid
asteroid respawning
(nice to have) bullets should do line collision test
*/

int main(int argc, char** argv)
{

	Application* myApp = Application::getInstace();
	myApp->run();
	delete myApp;

	return 0;
}