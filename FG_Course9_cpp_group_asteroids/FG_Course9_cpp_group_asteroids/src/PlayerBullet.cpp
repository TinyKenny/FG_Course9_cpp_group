#include "PlayerBullet.h"
#include <iostream>
#include <chrono>

PlayerBullet::PlayerBullet(Vector2 direction, Vector2 startPosition)
{
	std::vector<Vector2> points;
	points.push_back({ 0, 0 });
	points.push_back({0 , 0 });

	setPoints(points);

	velocity = { (direction.x * bulletSpeed) , (direction.y * bulletSpeed) };

	position = startPosition;
}

bool PlayerBullet::updateLifetime(double dt)
{
	secondsActive += dt;

	if (secondsActive >= lifeTime)
	{
		return false;
	}

	return true;
}
