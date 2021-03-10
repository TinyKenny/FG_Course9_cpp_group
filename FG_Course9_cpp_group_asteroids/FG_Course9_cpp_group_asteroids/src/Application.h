#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "UFO.h"
#include "Asteroid.h"
#include "PlayerBullet.h"
#include "PlayerSpaceship.h"

#include <SDL.h>

#include <vector>


class Application
{
private:
	Window* myWindow = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool keepApplicationAlive = false;
	bool keepGameLoopAlive = false;
	std::vector<UFO> UFOs;
	std::vector<Asteroid> asteroids;
	std::vector<PlayerBullet> playerBullets;
	PlayerSpaceship player;
	double dt;
	int currentScore;
	int highScore;

	TTF_Font* font = nullptr; // pool this maybe?
	SDL_Texture* gameOverMessageTexture = nullptr;
	SDL_Rect gameOverMessageSrcRect;
	SDL_Rect gameOverMessageDstRect;
	int paddingBetweenGameOverMessageAndScore;
	SDL_Texture* currentScoreTexture = nullptr;
	SDL_Rect currentScoreSrcRect;
	SDL_Rect currentScoreDstRect;

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
	void gameplayState();
	const void renderScene();
	Vector2 generateHazardSpawnPoint();
	void spawnUFOs();
	void spawnAsteroids();
	void updateBullets();
	void increaseCurrentScore();
	void resetCurrentScore();
	void rasterizeCurrentScoreText();
	void gameOverState();
};

#endif // !APPLICATION_H