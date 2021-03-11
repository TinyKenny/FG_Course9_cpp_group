#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadedFonts["default"] = TTF_OpenFont("res/comic.ttf", 20);
	loadedSounds["shot"] = Mix_LoadWAV("res/shot.wav");
	loadedSounds["hit"] = Mix_LoadWAV("res/hit.wav");
}

ResourceManager::~ResourceManager()
{
	for (auto const& x : loadedSounds)
	{
		Mix_FreeChunk(x.second);
	}
}

TTF_Font* ResourceManager::getFont(const std::string& name)
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

Mix_Chunk* ResourceManager::getSoundClip(const std::string& name)
{
	auto chunk = loadedSounds.find(name);

	if (chunk == loadedSounds.end())
	{

		return nullptr;
	}
	else
	{
		return chunk->second;
	}
}