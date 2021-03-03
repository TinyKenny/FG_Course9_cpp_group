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
	const int WINDOW_WIDTH = 600;
	const int WINDOW_HEIGHT = 400;

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
	void gameOver();
private:
	void runGameLoop();
	const void renderScene();
	void spawnAsteroids();
};

#endif // !APPLICATION_H