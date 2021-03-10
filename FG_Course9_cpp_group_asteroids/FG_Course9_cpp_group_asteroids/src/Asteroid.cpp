#include "Asteroid.h"
#include "Application.h"

Asteroid::Asteroid(Vector2 spawnPoint)
{
	position = spawnPoint;

	std::vector<Vector2> points;
	points.push_back({ 10, 0 });
	points.push_back({ 10, 5 });
	points.push_back({ 5, 10 });
	points.push_back({ 0, 10 });
	points.push_back({ -5, 10 });
	points.push_back({ -10, 5 });
	points.push_back({ -10, 0 });
	points.push_back({ -10, -5 });
	points.push_back({ -5, -10 });
	points.push_back({ 0, -10 });
	points.push_back({ 5, -10 });
	points.push_back({ 10, -5 });

	setPoints(points);

	generateVelocity();
}

void Asteroid::DestroyAsteroid(Application* app)
{
	app->DestroyAsteroid(this);
}

void Asteroid::generateVelocity()
{
	//get components for vector towards center
	double centerVectorX = (WINDOW_WIDTH / 2.0) - (position.x);
	double centerVectorY= (WINDOW_HEIGHT / 2.0) - (position.y);

	//get current magnitude
	double magnitude = sqrt((centerVectorX * centerVectorX) + (centerVectorY * centerVectorY));

	//deviate path from center by random degree
	double val = (double)rand() / (double)RAND_MAX;
	double modifier = (double)rand() / (double)RAND_MAX;

	if (val > 0.5f)
	{
		centerVectorX += modifier * magnitude;
	}
	else
	{
		centerVectorY += modifier * magnitude;
	}

	//get modified magnitude
	double newMagnitude = sqrt((centerVectorX * centerVectorX) + (centerVectorY * centerVectorY));

	//normalize components
	centerVectorX = centerVectorX / newMagnitude;
	centerVectorY = centerVectorY / newMagnitude;

	//generate new magnitude
	magnitude = (double) (rand() % (maxVelocity - minVelocity +1) )+ minVelocity;

	//apply
	centerVectorX *= magnitude;
	centerVectorY *= magnitude;

	GameObject::velocity = { (float)centerVectorX,(float)centerVectorY };
}

