#include "GameObject.h"

#include <iostream>

GameObject::GameObject() : position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f })
{
}

void GameObject::setPoints(std::vector<Vector2> pointsToSet)
{
	points = pointsToSet;
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

const std::vector<Vector2> GameObject::getPoints()
{
	std::vector<Vector2> worldPoints;
	worldPoints.reserve(points.size());
	for (int i = 0; i < points.size(); i++)
	{
		Vector2 worldSpacePoint;
		// TODO apply rotation
		worldSpacePoint.x = position.x + points[i].x;
		worldSpacePoint.y = position.y + points[i].y;
		worldPoints.push_back(worldSpacePoint);
	}
	return worldPoints;
}
