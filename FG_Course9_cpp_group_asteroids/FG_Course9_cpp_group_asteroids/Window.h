#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400


class Window
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Window();
public:
	~Window();
	static Window* getInstance();
	SDL_Renderer* getRenderer();
private:
	void initSDL();
};

#endif // !WINDOW_H