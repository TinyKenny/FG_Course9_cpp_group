#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2.h"

class Particle
{
public:
	Vector2 position;
	Vector2 velocity;
	float lifeTimeLeft;

	Particle();
};


#endif // !PARTICLE_H