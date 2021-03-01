#ifndef APPLICATION_H
#define APPLICATION_H

#include "GameObject.h"

#include <vector>

class Application
{
public:
	// public vars here
private:
	bool keepGameLoopAlive = false;
	std::vector<GameObject> gameObjects;
	Application(); // made this private to prevent stack-allocated Application-objects
public:
	static Application* getInstace();
	void run();
private:
	void runGameLoop();
};

#endif // !APPLICATION_H