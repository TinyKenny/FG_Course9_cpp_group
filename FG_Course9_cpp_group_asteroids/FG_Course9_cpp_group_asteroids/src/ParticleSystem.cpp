#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
	:activeParticleCount(0),
	activeParticlesStartIndex(0),
	activeParticlesEndIndex(0)
{
}

void ParticleSystem::spawnParticles(size_t particleCount, Vector2 origin, float particleDuration)
{
	/*
	if ((particlesActiveState.size() - activeParticleCount) > 0)
	{
		for (size_t i = 0; particleCount > 0 && i < particlesActiveState.size(); ++i)
		{
			if (!particlesActiveState[i])
			{
				particles[i].lifeTimeLeft
			}
		}
	}
	*/
	//for(size_t i = 0; i < )
}

void ParticleSystem::clearAllParticles()
{
	// TODO
}

void ParticleSystem::updateParticles(const double dt)
{
	// TODO
}

void ParticleSystem::draw(const SDL_Renderer* renderer) const
{
	// TODO
	// render draw point
}
