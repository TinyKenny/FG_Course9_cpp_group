#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadedFonts["default"] = TTF_OpenFont("res/comic.ttf", 20);
}

TTF_Font* ResourceManager::GetFont(const std::string& name)
{
	auto font = loadedFonts.find(name);

	if (font == loadedFonts.end())
	{
		return nullptr;
	}
	else
	{
		return font->second;
	}
}
