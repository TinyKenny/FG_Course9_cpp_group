#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Application;

class Asteroid : public GameObject
{
public:
	Asteroid(/*Vector2 spawnPoint*/) = delete;
	Asteroid(Vector2 spawnPoint);

private:
	//double xPos;
	//double yPos;
	int maxVelocity = 10;
	int minVelocity = 60;

	void generateVelocity();
};

#endif // ASTEROID_H

