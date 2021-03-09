#include "InputHandler.h"

#include "Application.h"

std::set<SDL_Keycode> InputHandler::keysDown;
std::set<SDL_Keycode> InputHandler::keysHeld;
std::set<SDL_Keycode> InputHandler::keysReleased;

void InputHandler::updateInputs(Application* app)
{
	for (SDL_Keycode key : keysDown)
	{
		keysHeld.insert(key);
	}
	keysDown.clear();
	for (SDL_Keycode key : keysReleased)
	{
		keysHeld.erase(key);
	}
	keysReleased.clear();

	SDL_Event eve;
	while (SDL_PollEvent(&eve))
	{
		switch (eve.type)
		{
		case SDL_QUIT:
			app->quit();
			break;
		case SDL_KEYDOWN:
			if (!eve.key.repeat)
			{
				keysDown.insert(eve.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			keysReleased.insert(eve.key.keysym.sym);
		}
	}
}

bool InputHandler::getKeyDown(SDL_Keycode key)
{
	return keysDown.count(key);
}

bool InputHandler::getKeyHeld(SDL_Keycode key)
{
	return keysHeld.count(key);
}

bool InputHandler::getKeyReleased(SDL_Keycode key)
{
	return keysReleased.count(key);
}

void InputHandler::clearAllKeys()
{
	keysDown.clear();
	keysHeld.clear();
	keysReleased.clear();
}
