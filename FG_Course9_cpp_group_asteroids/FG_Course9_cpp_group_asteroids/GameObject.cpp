#include "GameObject.h"

void GameObject::Update(double dt)
{
}

void GameObject::setPoints(std::vector<Vector2> pointsToSet)
{
	points = pointsToSet;
}

std::vector<Vector2> GameObject::getPoints()
{
	return points;
}
