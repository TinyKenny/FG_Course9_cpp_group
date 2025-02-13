#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Vector2.h"
#include "Particle.h"

#include <SDL.h>

#include <vector>

class ParticleSystem
{
public:
	ParticleSystem();
	void spawnParticles(const size_t particleCount, const Vector2 origin, const float particleDuration);
	void clearAllParticles();
	void updateParticles(const double dt);
	void draw(SDL_Renderer* renderer) const;
private:
	static constexpr float particleSpeed = 10.0f;
	size_t activeParticleCount;
	size_t activeParticlesStartIndex;
	size_t activeParticlesEndIndex;
	std::vector<Particle> particles;
	std::vector<bool> particlesActiveState;
};


#endif // !PARTICLE_SYSTEM_H