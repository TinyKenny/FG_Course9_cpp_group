#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid();
	
	void Update(double dt) override;
};

#endif // ASTEROID_H

