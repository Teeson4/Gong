#include "AssetManager.h"
#include "Game.h"

// STATIC INSTANCE
AssetManager* AssetManager::s_Instance;

// TEXTURE MANAGEMENT
// Load, render, and get textures
void AssetManager::loadTexture(std::string path)
{
	// Final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "[" << ASSET_TAG << "] (ERROR) Unable to load image \"" << path << "\". SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(&g_Game->getRenderer(), loadedSurface);

		if (newTexture == NULL)
		{
			std::cout << "[" << ASSET_TAG << "] (ERROR) Unable to create texture from \"" << path << "\". SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			SDL_Point dimensions = { loadedSurface->w, loadedSurface->h };

			m_Textures_W[path] = loadedSurface->w;
			m_Textures_H[path] = loadedSurface->h;

			m_Textures[path] = newTexture;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

SDL_Texture* AssetManager::getTexture(std::string path)
{
	if (m_Textures[path] == NULL)
	{
		std::cout << "[" << ASSET_TAG << "] (ERROR) Unable to get texture from \"" << path << "\". Textures must be loaded during initialization!" << std::endl;
	}

	return m_Textures[path];
}

int AssetManager::getTextureWidth(std::string path)
{
	if (m_Textures[path] == NULL)
	{
		std::cout << "[" << ASSET_TAG << "] (ERROR) Unable to get texture from \"" << path << "\". Textures must be loaded during initialization!" << std::endl;
	}
	
	return m_Textures_W[path];
}

int AssetManager::getTextureHeight(std::string path)
{
	if (m_Textures[path] == NULL)
	{
		std::cout << "[" << ASSET_TAG << "] (ERROR) Unable to get texture from \"" << path << "\". Textures must be loaded during initialization!" << std::endl;
	}

	return m_Textures_H[path];
}

// RENDERING STATE
// Render textures, fonts
void AssetManager::render(std::string path, float destX, float destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH)
{
	if (destW == NULL)
		destW = m_Textures_W[path];
	if (destH == NULL)
		destH = m_Textures_H[path];
	if (srcX == NULL)
		srcX = 0;
	if (srcY == NULL)
		srcY = 0;
	if (srcW == NULL)
		srcW = m_Textures_W[path];
	if (srcH == NULL)
		srcH = m_Textures_H[path];

	SDL_Rect srcRect = { srcX, srcY, srcW, srcH };
	SDL_FRect destRect = { destX, destY, (float) destW, (float) destH };

	SDL_RenderCopyExF(&g_Game->getRenderer(), m_Textures[path], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

// DISPOSITION STATE
// Delete instance, dispose resources
void AssetManager::dispose()
{
	// Dispose textures
	for (auto texture : m_Textures)
	{
		if (texture.second != NULL)
		{
			SDL_DestroyTexture(texture.second);
		}
	}

	m_Textures.clear();
	m_Textures_W.clear();
	m_Textures_H.clear();

	delete s_Instance;
	s_Instance = NULL;
}
