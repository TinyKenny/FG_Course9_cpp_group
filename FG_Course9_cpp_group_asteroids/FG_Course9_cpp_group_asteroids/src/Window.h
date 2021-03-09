#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400


class Window
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	bool setupSuccessful = false;
	Window();
public:
	~Window();
	static Window* getInstance();
	SDL_Renderer* getRenderer();
	TTF_Font* getFont();
	bool wasSetUpSuccessfully();
private:
	void initSDL();
};

#endif // !WINDOW_H