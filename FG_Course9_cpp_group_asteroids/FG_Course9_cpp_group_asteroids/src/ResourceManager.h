#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SDL_ttf.h"
#include "iostream"
#include <SDL.h>
#include <map>
#include <memory>

class ResourceManager
{
public:
	ResourceManager();

	TTF_Font* GetFont(const std::string& name);

private:
	std::map<std::string, TTF_Font*> loadedFonts;
};

#endif

