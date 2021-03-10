#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Vector2.h"

#include <SDL.h>

#include <vector>

class ParticleSystem
{
public:
	void spawnParticles(const Vector2 origin, const int particleCount);
	void clearAllParticles();
	void updateParticles(const double dt);
	void draw(const SDL_Renderer* renderer) const;
private:
	//std::vector
};


#endif // !PARTICLE_SYSTEM_H