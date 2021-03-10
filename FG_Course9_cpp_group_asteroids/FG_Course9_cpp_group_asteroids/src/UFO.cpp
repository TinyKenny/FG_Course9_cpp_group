#include "UFO.h"

#define SCALE 1.0

#include <iostream>

UFO::UFO(Vector2 spawnPoint, PlayerSpaceship* playerObject)
{
	// TODO generate spawn point
	player = playerObject;
	position = spawnPoint;

	std::vector<Vector2> points;

	Vector2 a = { 20.0f, 0.0f };
	Vector2 b = { 8.0f, 4.0f };
	Vector2 c = { 4.0f, 8.0f };
	
	points.push_back(Vector2({ -a.x, -a.y }) * SCALE);
	points.push_back(Vector2({ -b.x, -b.y }) * SCALE);
	points.push_back(Vector2({ -c.x, -c.y }) * SCALE);
	points.push_back(Vector2({ c.x, -c.y }) * SCALE);
	points.push_back(Vector2({ b.x, -b.y }) * SCALE);
	points.push_back(Vector2({ a.x, a.y }) * SCALE);
	points.push_back(Vector2({ b.x, b.y }) * SCALE);
	points.push_back(Vector2({ c.x, c.y }) * SCALE);
	points.push_back(Vector2({ -c.x, c.y }) * SCALE);
	points.push_back(Vector2({ -b.x, b.y }) * SCALE);

	setPoints(points);
}

void UFO::update()
{
	velocity = player->position - position;
	velocity.setMagnitude(speed);
}
