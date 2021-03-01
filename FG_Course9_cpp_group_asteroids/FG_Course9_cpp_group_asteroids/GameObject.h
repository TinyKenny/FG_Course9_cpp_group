#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"

#include <vector>

class GameObject
{
public:
	void Update(double dt);
private:
	// TODO GameObjects should have positions
	// TODO GameObjects should have a list of points, for rendering and collision
	std::vector<Component> components;
};

#endif // !GAME_OBJECT_H