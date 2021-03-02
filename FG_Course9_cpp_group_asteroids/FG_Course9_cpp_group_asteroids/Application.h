#ifndef APPLICATION_H
#define APPLICATION_H

//#include "Window.h"
#include "GameObject.h"

#include <SDL.h>

#include <vector>

class Application
{
public:
	// public vars here
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool keepGameLoopAlive = false;
	std::vector<GameObject> gameObjects;
	Application(); // made this private to prevent stack-allocated Application-objects
	void initSDL();
public:
	~Application();
	static Application* getInstace();
	void run();
	void quit();
private:
	void runGameLoop();
	const void renderScene();
};

#endif // !APPLICATION_H