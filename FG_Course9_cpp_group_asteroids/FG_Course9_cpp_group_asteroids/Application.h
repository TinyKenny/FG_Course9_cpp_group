#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Asteroid.h"
#include "PlayerBullet.h"
#include "PlayerSpaceship.h"

#include <SDL.h>

#include <vector>


class Application
{
private:
	Window* myWindow;
	SDL_Renderer* renderer;
	bool keepApplicationAlive = false;
	bool keepGameLoopAlive = false;
	std::vector<Asteroid> asteroids;
	std::vector<PlayerBullet> playerBullets;
	PlayerSpaceship player;
	double dt;
	Application(Window* window); // made this private to prevent stack-allocated Application-objects
public:
	Application() = delete; // dont allow instances of application without window
	~Application();
	static Application* getInstace(Window* window);
	void run();
	void quit();
	void gameOver();
	void spawnBullet(Vector2 direction, Vector2 startPosition);
	void DestroyAsteroid(Asteroid *asteroid);
private:
	void GameplayState();
	const void renderScene();
	void spawnAsteroids();
	void updateBullets();
	void gameOverState();
};

#endif // !APPLICATION_H