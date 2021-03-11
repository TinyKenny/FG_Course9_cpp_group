#include "ParticleSystem.h"

#include <math.h>
#include <iostream>

#define TAU M_PI * 2.0

ParticleSystem::ParticleSystem()
	:activeParticleCount(0),
	activeParticlesStartIndex(0),
	activeParticlesEndIndex(0)
{
}

void ParticleSystem::spawnParticles(const size_t particleCount, const Vector2 origin, const float particleDuration)
{
	if (particleCount == 0)
	{
		return;
	}

	size_t particlesLeft = particleCount;
	double angleStepSizeRad = TAU / particleCount;
	

	if ((particlesActiveState.size() - activeParticleCount) > 0)
	{
		for (size_t i = 0; particlesLeft > 0 && i < particlesActiveState.size(); ++i)
		{
			if (!particlesActiveState[i])
			{
				particlesActiveState[i] = true;
				particles[i].position = origin;
				double currentAngle = angleStepSizeRad * (particleCount - particlesLeft);
				particles[i].velocity = { (float)cos(currentAngle) * particleSpeed, (float)sin(currentAngle) * particleSpeed };
				particles[i].lifeTimeLeft = particleDuration;

				if (activeParticleCount == 0)
				{
					activeParticlesStartIndex = i;
					activeParticlesEndIndex = i;
				}
				else if (i < activeParticlesStartIndex)
				{
					activeParticlesStartIndex = i;
				}
				else if (activeParticlesEndIndex < i)
				{
					activeParticlesEndIndex = i;
				}
				
				--particlesLeft;
				++activeParticleCount;
			}
		}
	}

	while (particlesLeft > 0)
	{
		Particle toAdd;
		toAdd.position = origin;
		double currentAngle = angleStepSizeRad * (particleCount - particlesLeft);
		toAdd.velocity = { (float)cos(currentAngle) * particleSpeed, (float)sin(currentAngle) * particleSpeed };
		toAdd.lifeTimeLeft = particleDuration;
		particles.push_back(toAdd);
		particlesActiveState.push_back(true);

		activeParticlesEndIndex = particlesActiveState.size() - 1;

		--particlesLeft;
		++activeParticleCount;
	}
}

void ParticleSystem::clearAllParticles()
{
	activeParticleCount = 0;
	activeParticlesStartIndex = 0;
	activeParticlesEndIndex = 0;
	for (size_t i = 0; i < particlesActiveState.size(); ++i)
	{
		particlesActiveState[i] = false;
	}
}

void ParticleSystem::updateParticles(const double dt)
{
	size_t oldActiveParticleCount = activeParticleCount;
	for (size_t i = 0; i < particlesActiveState.size(); ++i)
	{
		if (particlesActiveState[i])
		{
			particles[i].position += particles[i].velocity * dt;
			particles[i].lifeTimeLeft -= (float)dt;

			if (particles[i].lifeTimeLeft <= 0.0f)
			{
				particlesActiveState[i] = false;
				activeParticleCount--;
			}
		}
	}

	if (activeParticleCount == 0)
	{
		activeParticlesStartIndex = 0;
		activeParticlesEndIndex = 0;
	}
	if (activeParticleCount != oldActiveParticleCount)
	{
		for (size_t i = 0; i < particlesActiveState.size(); ++i)
		{
			if (particlesActiveState[i])
			{
				activeParticlesStartIndex = i;
				break;
			}
		}

		for (int i = particlesActiveState.size() - 1; i >= 0; --i)
		{
			if (particlesActiveState[i])
			{
				activeParticlesEndIndex = i;
				break;
			}
		}
	}
}

void ParticleSystem::draw(SDL_Renderer* renderer) const
{
	if (activeParticleCount > 0)
	{
		for (size_t i = activeParticlesStartIndex; i <= activeParticlesEndIndex; ++i)
		{
			if (particlesActiveState[i])
			{
				SDL_RenderDrawPointF(renderer, particles[i].position.x, particles[i].position.y);
			}
		}
	}
}
