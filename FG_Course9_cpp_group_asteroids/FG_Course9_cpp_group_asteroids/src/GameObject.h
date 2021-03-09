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
	virtual std::vector<Vector2> getPoints() const;
	float getCircleRadius() const;
protected:
	std::vector<Vector2> points;
private:
	float circleRadius = 0.0f;
};

#endif // !GAME_OBJECT_H
