#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include "Vector2.h"

#include <vector>

class GameObject
{
public:
	Vector2 velocity;
	void Update(double dt);
	void setPoints(std::vector<Vector2> pointsToSet);
	std::vector<Vector2> getPoints();
private:
	// TODO GameObjects should have position and rotation
	// TODO GameObjects should have a list of points, for rendering and collision
	std::vector<Vector2> points;
	std::vector<Component> components;
};

#endif // !GAME_OBJECT_H