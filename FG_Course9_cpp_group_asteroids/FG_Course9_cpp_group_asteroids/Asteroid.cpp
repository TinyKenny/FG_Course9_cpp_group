#include "Asteroid.h"

double xPos;
double yPos;

Asteroid::Asteroid(SDL_Window* window)
{
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

	generateSpawnPoint(window);
	generateVelocity(20,200);
}

//TODO: Magic numbers, refactor
void Asteroid::generateSpawnPoint(SDL_Window* window)
{
	windowWidth = new int();
	windowHeight = new int();


	SDL_GetWindowSize(window, windowWidth, windowHeight);

	
	double val = (double)rand() / (double)RAND_MAX;
	double modifier = (double)rand() / (double)RAND_MAX;

	if (val > 0.5)
	{
		if (val > 0.75)
		{
			xPos = 0;
		}
		else
		{
			xPos = (double) *windowWidth;
		}

		yPos = (double) *windowHeight * modifier;
	}
	else
	{
		if (val > 0.25)
		{
			yPos = 0;
		}
		else
		{
			yPos = (double) *windowHeight;
		}

		xPos = (double)*windowWidth * modifier;
	}

	position = {(float)xPos, (float)yPos};
	
}

//TODO: FIX CASTING CLUSTERFUDGE, Magic numbers, refactor
void Asteroid::generateVelocity(int min, int max)
{
	//get components for vector towards center
	double centerVectorX = (*windowWidth / 2.0) - (position.x);
	double centerVectorY= (*windowHeight / 2.0) - (position.y);

	//get current magnitude
	double magnitude = sqrt((centerVectorX * centerVectorX) + (centerVectorY * centerVectorY));

	//deviate path from center by random degree
	double val = (double)rand() / (double)RAND_MAX;
	float modifier = (double)rand() / (double)RAND_MAX / 2;

	if (val > 0.5f)
	{
		centerVectorX += modifier * magnitude;
	}
	else
	{
		centerVectorY += modifier * magnitude;
	}

	//normalize components
	centerVectorX = centerVectorX / magnitude;
	centerVectorY = centerVectorY / magnitude;

	//generate new magnitude
	magnitude = (double) (rand() % (max - min +1) )+ min;

	//apply
	centerVectorX *= magnitude;
	centerVectorY *= magnitude;


	GameObject::velocity = { (float)centerVectorX,(float)centerVectorY };
}

