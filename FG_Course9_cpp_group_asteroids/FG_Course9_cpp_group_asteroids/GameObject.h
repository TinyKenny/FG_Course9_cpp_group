#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector2.h"

#include <SDL.h>

#include <vector>

class GameObject
{
public:
	GameObject();
	Vector2 position;
	Vector2 velocity;
	virtual void draw(SDL_Renderer* renderer);
	void setPoints(std::vector<Vector2> pointsToSet);
	const virtual std::vector<Vector2> getPoints();
protected:
	std::vector<Vector2> points;
};

#endif // !GAME_OBJECT_H
