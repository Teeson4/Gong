#pragma once

#include <SDL.h>
#include <string>

class Button
{

private:

	std::string m_Path;

	SDL_FRect m_DestRect;
	SDL_Rect m_SrcRect;

	int m_Width, m_Height;

	bool m_Hover;
	bool m_Pressed;
	bool m_Released;

public:

	Button(std::string path, int width, int height, SDL_FRect destRect, SDL_Rect srcRect);

	void input(int& currentChoice, int thisChoice);
	void update();
	void render();

	inline bool isHover() { return m_Hover; }
	inline bool isPressed() { return m_Pressed; }
	inline bool isReleased() { return m_Released; }

};
