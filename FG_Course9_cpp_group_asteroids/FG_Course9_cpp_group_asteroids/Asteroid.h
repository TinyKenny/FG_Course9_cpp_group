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
	int* windowWidth;
	int* windowHeight;

private:
	void generateSpawnPoint(SDL_Window* window);
	void generateVelocity(int min, int max);
};

#endif // ASTEROID_H

