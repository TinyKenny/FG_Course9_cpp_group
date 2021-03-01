#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "GameObject.h"

#include <vector>

class Window
{
public:
	Window();
	~Window();
	bool initializedSuccessfully();
	void testRender();
	void render(const std::vector<GameObject>& gameObjects);
private:
	void initialize();
	bool initSuccessful = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !WINDOW_H
