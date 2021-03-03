#include "GameObject.h"

#include <iostream>

GameObject::GameObject() : position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f })
{
}

void GameObject::setPoints(std::vector<Vector2> pointsToSet)
{
	points = pointsToSet;

	for (size_t i = 0; i < points.size(); i++)
	{
		float distanceToCenter = points[i].magnitude();
		if (distanceToCenter > circleRadius)
		{
			circleRadius = distanceToCenter;
		}
	}
}

void GameObject::draw(SDL_Renderer* renderer)
{
	std::vector<Vector2> worldPoints = getPoints();

	int pointCount = worldPoints.size();
	for (int i = 0; i < pointCount; ++i)
	{
		SDL_RenderDrawLineF(renderer, worldPoints[i].x,
									  worldPoints[i].y,
									  worldPoints[(i + 1) % pointCount].x,
									  worldPoints[(i + 1) % pointCount].y);
	}
}

std::vector<Vector2> GameObject::getPoints() const
{
	std::vector<Vector2> worldPoints;
	worldPoints.reserve(points.size());
	for (int i = 0; i < points.size(); i++)
	{
		worldPoints.push_back(position + points[i]);
	}
	return worldPoints;
}

float GameObject::getCircleRadius() const
{
	return circleRadius;
}
