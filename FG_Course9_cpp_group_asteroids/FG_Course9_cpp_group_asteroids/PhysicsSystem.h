#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "Asteroid.h"
#include "PlayerBullet.h"
#include "PlayerSpaceship.h"


#include <vector>

class Application;

class PhysicsSystem
{
public:
	static void physicsUpdate(Application* app, double dt,
							  std::vector<Asteroid>& asteroids,
							  std::vector<PlayerBullet>& playerBullets,
							  PlayerSpaceship& player);
	
	static void wrapAround(GameObject &go, int windowWidth, int windowHeight);
};

#endif // !PHYSICS_SYSTEM_H