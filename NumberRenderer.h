#pragma once

#include <SDL.h>

const int NUM_TEXTURE_SIZE = 256;
const int NUM_UNIT_SIZE = 32;

class NumberRenderer
{

private:

	static NumberRenderer* s_Instance;

	SDL_Rect m_0Rect, m_1Rect, m_2Rect, m_3Rect, m_4Rect, m_5Rect, m_6Rect, m_7Rect, m_8Rect, m_9Rect;

public:

	static NumberRenderer* instance()
	{
		if (s_Instance == NULL)
			s_Instance = new NumberRenderer();

		return s_Instance;
	}

	void init();
	
	void render(int num, float destX, float destY, float scale, SDL_Color color);
	void render();
	void renderNumPopUp(int num, float destX, float destY, float scale, SDL_Color color);

	int getNumWidth(int num, float scale);

};

#define g_NumberRenderer NumberRenderer::instance()
