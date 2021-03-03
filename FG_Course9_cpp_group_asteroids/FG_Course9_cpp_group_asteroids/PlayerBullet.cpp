#include "PlayerBullet.h"
#include <iostream>

PlayerBullet::PlayerBullet(Vector2 direction, Vector2 startPosition)
{
	std::vector<Vector2> points;
	points.push_back({ 0, 0 });
	points.push_back({0 , 0 });

	std::cout << startPosition.x << ", " << startPosition.y << std::endl;

	setPoints(points);

	velocity = { (direction.x * bulletSpeed) , (direction.y * bulletSpeed) };

	position = startPosition;
}
