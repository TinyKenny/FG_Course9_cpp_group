#include "Asteroid.h"
#include "Application.h"
#include "stdlib.h"
#include <random>
#include <time.h>
#include <iostream>


float xPos;
float yPos;

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

	//GameObject::velocity = { 100,100 };
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

	
	float val = (float)rand() / (float)RAND_MAX;
	float modifier = (float)rand() / (float)RAND_MAX;

	if (val > 0.5)
	{
		if (val > 0.75)
		{
			xPos = 0;
		}
		else
		{
			xPos = (float) *windowWidth;
		}

		yPos = (float) *windowHeight * modifier;
	}
	else
	{
		if (val > 0.25)
		{
			yPos = 0;
		}
		else
		{
			yPos = (float) *windowHeight;
		}

		xPos = (float)*windowWidth * modifier;
	}


	position = {xPos, yPos};
	
}

//TODO: Magic numbers, refactor
void Asteroid::generateVelocity(int min, int max)
{
	//get components for vector towards center
	float centerVectorX = (*windowWidth / 2.0f) - (position.x);
	float centerVectorY= (*windowHeight / 2.0f) - (position.y);

	//get current magnitude
	float magnitude = sqrt((centerVectorX * centerVectorX) + (centerVectorY * centerVectorY));

	//deviate path from center by random degree
	float val = (float)rand() / (float)RAND_MAX;
	float modifier = (float)rand() / (float)RAND_MAX / 2;

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
	magnitude = rand() % (max - min +1) + min;

	//apply
	centerVectorX *= magnitude;
	centerVectorY *= magnitude;


	GameObject::velocity = { centerVectorX,centerVectorY };
}

