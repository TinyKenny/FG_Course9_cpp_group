#include "Asteroid.h"
#include "Application.h"

Asteroid::Asteroid()
{
	std::vector<Vector2> points;
	points.push_back({ 50, 10 });
	points.push_back({ 60, 20 });
	points.push_back({ 70, 30 });
	points.push_back({ 70, 60 });
	points.push_back({ 60, 70 });
	points.push_back({ 50, 80 });
	points.push_back({ 40, 90 });
	points.push_back({ 40, 90 });

	setPoints(points);
};