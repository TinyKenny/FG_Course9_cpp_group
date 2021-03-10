#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadedFonts["default"] = TTF_OpenFont("res/comic.ttf", 20);
}

TTF_Font* ResourceManager::GetFont(const std::string& name)
{
	return nullptr;
}
