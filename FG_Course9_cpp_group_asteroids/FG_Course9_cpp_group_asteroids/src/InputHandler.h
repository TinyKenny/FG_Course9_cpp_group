#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <set>

#include <SDL.h>

class Application;

class InputHandler
{
public:
	static void updateInputs(Application* app);
	static bool getKeyDown(SDL_Keycode key);
	static bool getKeyHeld(SDL_Keycode key);
	static bool getKeyReleased(SDL_Keycode key);
	static void clearAllKeys();
private:
	static std::set<SDL_Keycode> keysDown;
	static std::set<SDL_Keycode> keysHeld;
	static std::set<SDL_Keycode> keysReleased;
};

#endif // !INPUT_HANDLER_H