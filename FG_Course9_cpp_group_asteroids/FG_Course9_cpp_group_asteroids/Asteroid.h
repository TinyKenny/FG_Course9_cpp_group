#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Application;

class Asteroid : public GameObject
{
public:
	Asteroid();
	void DestroyAsteroid(Application* app);

private:
	double xPos;
	double yPos;
	int maxVelocity = 10;
	int minVelocity = 60;

private:
	void generateSpawnPoint();
	void generateVelocity();
};

#endif // ASTEROID_H

