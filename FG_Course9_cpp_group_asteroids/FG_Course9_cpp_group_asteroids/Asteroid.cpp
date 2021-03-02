#include "Asteroid.h"
#include "Application.h"

Asteroid::Asteroid()
{
	std::vector<Vector2> points;
	points.push_back({ 55, 10 });
	points.push_back({ 60, 20 });
	points.push_back({ 65, 25 });
	points.push_back({ 65, 45 });
	points.push_back({ 60, 50 });
	points.push_back({ 55, 55 });
	points.push_back({ 35, 55 });
	points.push_back({ 25, 45 });
	points.push_back({ 25, 25 });
	points.push_back({ 35, 10 });

	GameObject::velocity = {100,100};
	setPoints(points);
}

