#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <map>

#define ASSET_TAG "AssetManager"

enum class TYPE
{
	TEXTURE = 0,
	FONT_TEXTURE = 1
};

class AssetManager
{

private:

	static AssetManager* s_Instance;

	std::map<std::string, SDL_Texture*> m_Textures;
	std::map<std::string, int> m_Textures_W;
	std::map<std::string, int> m_Textures_H;

public:

	static AssetManager* instance()
	{
		if (s_Instance == 0)
			s_Instance = new AssetManager();

		return s_Instance;
	}

	// TEXTURE MANAGEMENT
	void loadTexture(std::string path);
	SDL_Texture* getTexture(std::string path);
	int getTextureWidth(std::string path);
	int getTextureHeight(std::string path);

	// UNIVERSAL FUNCTIONS
	void render(std::string path, float destX, float destY, int destW = NULL, int destH = NULL, int srcX = NULL, int srcY = NULL, int srcW = NULL, int srcH = NULL);
	
	// DISPOSE
	void dispose();

};

#define g_AssetManager AssetManager::instance()
