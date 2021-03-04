#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Application;

class Asteroid : public GameObject
{
public:
	Asteroid(SDL_Window* window);
	void DestroyAsteroid(Application* app);

private:
	int windowWidth;
	int windowHeight;
	double xPos;
	double yPos;
	int maxVelocity = 20;
	int minVelocity = 100;

private:
	void generateSpawnPoint(SDL_Window* window);
	void generateVelocity();
};

#endif // ASTEROID_H

