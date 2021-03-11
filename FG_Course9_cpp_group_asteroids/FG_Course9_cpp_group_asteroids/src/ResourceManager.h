#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SDL_ttf.h"
#include "iostream"
#include <SDL.h>
#include <map>
#include <memory>
#include <SDL_mixer.h>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	TTF_Font* getFont(const std::string& name);
	Mix_Chunk* getSoundClip(const std::string& name);

private:
	std::map<std::string, TTF_Font*> loadedFonts;
	std::map<std::string, Mix_Chunk*> loadedSounds;
};

#endif

