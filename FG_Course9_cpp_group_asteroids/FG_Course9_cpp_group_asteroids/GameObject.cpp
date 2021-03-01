#include "GameObject.h"

void GameObject::Update(double dt)
{
	for (Component comp : components)
	{
		comp.Update(dt);
	}
}

void GameObject::setPoints(std::vector<Vector2> pointsToSet)
{
	points = pointsToSet;
}

std::vector<Vector2> GameObject::getPoints()
{
	return points;
}
