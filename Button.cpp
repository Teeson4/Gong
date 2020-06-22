#include "Button.h"
#include "Game.h"

Button::Button(std::string path, int width, int height, SDL_FRect destRect, SDL_Rect srcRect)
{
	m_Path = path;
	m_DestRect = destRect;
	m_SrcRect = srcRect;

	m_Hover = false;
	m_Pressed = false;
	m_Released = false;

	m_Width = width;
	m_Height = height;
}

void Button::input(int& currentChoice, int thisChoice)
{
	m_Hover = false;
	m_Pressed = false;
	m_Released = false;

	if (currentChoice == thisChoice)
	{
		m_Hover = true;
	}

	if (m_Hover && g_InputManager->buttonDown(SDL_CONTROLLER_BUTTON_A))
	{
		m_Pressed = true;
	}

	if (m_Hover && g_InputManager->buttonReleased(SDL_CONTROLLER_BUTTON_A))
	{
		m_Released = true;
	}
}

void Button::update()
{
	m_SrcRect.y = 0;

	if (m_Hover)
		m_SrcRect.y = m_SrcRect.h;
	if (m_Pressed)
		m_SrcRect.y = m_SrcRect.h * 2;
}

void Button::render()
{
	SDL_RenderCopyExF(&g_Game->getRenderer(), g_AssetManager->getTexture(m_Path), &m_SrcRect, &m_DestRect, 0, 0, SDL_FLIP_NONE);
}
