#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include "Vector2.h"

#include <SDL.h>

#include <vector>

class GameObject
{
public:
	GameObject();
	Vector2 position;
	Vector2 velocity;
	virtual void Update(double dt);
	virtual void draw(SDL_Renderer* renderer);
	void setPoints(std::vector<Vector2> pointsToSet);
	const std::vector<Vector2> getPoints();

private:
	float idkMan;
	// TODO GameObjects should have position and rotation
	// TODO GameObjects should have a list of points, for rendering and collision
	std::vector<Vector2> points;
	std::vector<Component> components;
};

#endif // !GAME_OBJECT_H
