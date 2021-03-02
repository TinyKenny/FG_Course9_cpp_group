#ifndef APPLICATION_H
#define APPLICATION_H

#include "Asteroid.h"
#include "PlayerBullet.h"
#include "PlayerSpaceship.h"

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
	std::vector<Asteroid> asteroids;
	std::vector<PlayerBullet> playerBullets;
	PlayerSpaceship player;
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
	void spawnAsteroids();
};

#endif // !APPLICATION_H