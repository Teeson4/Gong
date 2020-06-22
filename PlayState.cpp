#include "PlayState.h"
#include "MainMenuState.h"

PlayState* PlayState::s_Instance;

void PlayState::init()
{
	Logger::info(PLAY_TAG, "Init");

	// Player & AI Score Zones
	m_PlayerScoreRect.w = m_AiScoreRect.w = 20;
	m_PlayerScoreRect.h = m_AiScoreRect.h = SCREEN_HEIGHT;

	// Center divider
	m_CenterLineRect.w = 5;
	m_CenterLineRect.h = SCREEN_HEIGHT;
	m_CenterLineRect.x = (SCREEN_WIDTH / 2) - (m_CenterLineRect.w / 2);
	m_CenterLineRect.y = 0;

	m_PlayerScoreRect.x = m_PlayerScoreRect.y = m_AiScoreRect.y = 0;
	m_AiScoreRect.x = SCREEN_WIDTH - m_AiScoreRect.w;

	// Entities
	g_Player->init();
	g_Enemy->init();
	g_Ball->init();

	// Handles
	m_ReadyToPlay = false;
	m_TriggerMainMenuState = false;
}

void PlayState::pause()
{
	Logger::info(PLAY_TAG, "Pause");
}

void PlayState::resume()
{
	Logger::info(PLAY_TAG, "Resume");
}

void PlayState::input(float delta)
{
	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_A))
	{
		m_ReadyToPlay = true;
	}

	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		g_Player->setPower(Power::SPIKE);
	}

	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		g_Player->setPower(Power::CURVE);
	}

	if (m_ReadyToPlay)
	{
		g_Player->input(delta);
		g_Enemy->input(delta);
		g_Ball->input(delta);
	}

	if (g_InputManager->keyPressed(SDL_SCANCODE_BACKSPACE))
	{
		g_Game->fadeOut();
		m_TriggerMainMenuState = true;
	}
}

void PlayState::update(float delta)
{
	if (m_ReadyToPlay)
	{
		g_Ball->update(delta);
		g_Player->update(delta);
		g_Enemy->update(delta);
	}

	if (!g_Game->isFadingOut())
	{
		if (m_TriggerMainMenuState)
		{
			g_GameStateManager->setState(g_MainMenuState);
			g_Game->fadeIn();
		}
	}

	if ((g_Player->getPower() == Power::SPIKE && g_Player->getPoints() < SPIKE_COST) || (g_Player->getPower() == Power::CURVE && g_Player->getPoints() < CURVE_COST))
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/power_select.png"), 127);
	}
	else
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/power_select.png"), 255);
	}

	if (g_Player->getPoints() >= SPIKE_COST)
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/spike_graphic.png"), 255);
	}
	else
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/spike_graphic.png"), 50);
	}

	if (g_Player->getPoints() >= CURVE_COST)
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/curve_graphic.png"), 255);
	}
	else
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/curve_graphic.png"), 50);
	}

	if (g_Player->m_Position.getY() + g_Player->getHeight() >= SCREEN_HEIGHT - 138)
	{
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/spike_graphic.png"), 25);
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/curve_graphic.png"), 25);
		SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/power_select.png"), 25);
	}
}

void PlayState::render()
{
	// Draw Score Zones
	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 0, 149, 233, 255);
	SDL_RenderFillRect(&g_Game->getRenderer(), &m_PlayerScoreRect);

	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 255, 0, 68, 255);
	SDL_RenderFillRect(&g_Game->getRenderer(), &m_AiScoreRect);

	// Draw Center Divider
	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 90, 105, 136, 255);
	SDL_RenderFillRect(&g_Game->getRenderer(), &m_CenterLineRect);

	// Power up hotbar
	g_AssetManager->render("Resources/Textures/spike_graphic.png", (SCREEN_WIDTH / 4) - (float) g_AssetManager->getTextureWidth("Resources/Textures/spike_graphic.png"), (SCREEN_HEIGHT - 138));

	g_AssetManager->render("Resources/Textures/curve_graphic.png", (SCREEN_WIDTH / 4), (SCREEN_HEIGHT - 138));

	switch (g_Player->getPower())
	{
	case Power::SPIKE:
		g_AssetManager->render("Resources/Textures/power_select.png", (float) (SCREEN_WIDTH / 4) - g_AssetManager->getTextureWidth("Resources/Textures/power_select.png"), (SCREEN_HEIGHT - 138));
		break;

	case Power::CURVE:
		g_AssetManager->render("Resources/Textures/power_select.png", (SCREEN_WIDTH / 4), (SCREEN_HEIGHT - 138));
		break;
	}

	g_Player->render();
	g_Enemy->render();

	// Draw Play Ready Screen
	if(!m_ReadyToPlay)
		g_AssetManager->render("Resources/Textures/play_ready_screen.png", 0, 0);

	SDL_SetTextureAlphaMod(g_AssetManager->getTexture("Resources/Textures/numbers.png"), 25);

	// Player Score
	g_NumberRenderer->render(g_Player->getScore(), (float) (SCREEN_WIDTH / 4) - (g_NumberRenderer->getNumWidth(g_Player->getScore(), 0.5f) / 2), 50.f, 0.5f, { 255, 255, 255 });

	g_NumberRenderer->render(g_Enemy->getScore(), (float) (SCREEN_WIDTH - (SCREEN_WIDTH / 4)) - (g_NumberRenderer->getNumWidth(g_Enemy->getScore(), 0.5f) / 2), 50.f, 0.5f, { 255, 255, 255 });

	g_NumberRenderer->render(g_Player->getPoints(), (float) (SCREEN_WIDTH / 4) - (g_NumberRenderer->getNumWidth(g_Player->getPoints(), 0.15f) / 2), 190.f, 0.15f, { 255, 255, 255 });

	// Render ball
	if (m_ReadyToPlay)
		g_Ball->render();
}

void PlayState::dispose()
{
	Logger::info(PLAY_TAG, "Dispose");
	// Begin dispose

	g_Player->dispose();
	g_Enemy->dispose();
	g_Ball->dispose();

	// End dispose
	delete s_Instance;
	s_Instance = NULL;
}