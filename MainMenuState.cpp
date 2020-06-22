#include "MainMenuState.h"

#include "Game.h"
#include "PlayState.h"

MainMenuState* MainMenuState::s_Instance;

void MainMenuState::init()
{
	Logger::info(MAINMENU_TAG, "Init");

	m_Choice = 0;

	m_Background1.w = 420;
	m_Background1.h = 380;
	m_Background1.x = (SCREEN_WIDTH / 2) - (m_Background1.w / 2);
	m_Background1.y = (SCREEN_HEIGHT / 2) - (m_Background1.h / 2) + 180;

	m_Background2.w = 350;
	m_Background2.h = 305;
	m_Background2.x = (SCREEN_WIDTH / 2) - (m_Background2.w / 2);
	m_Background2.y = (SCREEN_HEIGHT / 2) - (m_Background2.h / 2) + 180;

	m_PlayButton = new Button("Resources/Textures/play_button_64x18.png", 320, 90, { (SCREEN_WIDTH / 2) - (320 / 2), (SCREEN_HEIGHT / 2) - (80 / 2) + 85, 320, 90 }, { 0, 0, 320, 90 });

	m_OptionsButton = new Button("Resources/Textures/options_button_64x16.png", 320, 80, { (SCREEN_WIDTH / 2) - (320 / 2), (SCREEN_HEIGHT / 2) - (80 / 2) + 185, 320, 80 }, { 0, 0, 320, 80 });

	m_ExitButton = new Button("Resources/Textures/exit_button_64x16.png", 320, 100, { (SCREEN_WIDTH / 2) - (320 / 2), (SCREEN_HEIGHT / 2) - (80 / 2) + 275, 320, 80 }, { 0, 0, 320, 80 });

	m_TriggerPlayState = false;
	m_TriggerOptionsState = false;
}

void MainMenuState::pause()
{
	Logger::info(MAINMENU_TAG, "Pause");
}

void MainMenuState::resume()
{
	Logger::info(MAINMENU_TAG, "Resume");
}

void MainMenuState::input(float delta)
{
	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (m_Choice + 1 > MAX_CHOICE)
		{
			m_Choice = MAX_CHOICE;
		}
		else
		{
			m_Choice += 1;
		}
	}

	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_Choice - 1 < MIN_CHOICE)
		{
			m_Choice = MIN_CHOICE;
		}
		else
		{
			m_Choice -= 1;
		}
	}

	m_PlayButton->input(m_Choice, 0);
	m_OptionsButton->input(m_Choice, 1);
	m_ExitButton->input(m_Choice, 2);

	if (m_ExitButton->isReleased())
	{
		g_Game->setRunning(false);
	}

	if (m_OptionsButton->isReleased())
	{
		g_Game->fadeOut();
		Logger::info(MAINMENU_TAG, "Options!");
	}

	if (m_PlayButton->isReleased())
	{
		g_Game->fadeOut();
		m_TriggerPlayState = true;
	}
}

void MainMenuState::update(float delta)
{

	m_PlayButton->update();
	m_OptionsButton->update();
	m_ExitButton->update();

	if (!g_Game->isFadingOut())
	{
		if (m_TriggerPlayState)
		{
			g_GameStateManager->setState(g_PlayState);
			g_Game->fadeIn();
		}
		else if (m_TriggerOptionsState)
		{
			g_Game->fadeIn();
		}
	}
}

void MainMenuState::render()
{
	SDL_SetRenderDrawBlendMode(&g_Game->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 0, 0, 0, 75);
	SDL_RenderFillRect(&g_Game->getRenderer(), &m_Background1);

	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(&g_Game->getRenderer(), &m_Background2);

	g_AssetManager->render("Resources/Textures/main_menu_logo.png", (float) (SCREEN_WIDTH / 2) -  (g_AssetManager->getTextureWidth("Resources/Textures/main_menu_logo.png") / 2), 45);

	m_PlayButton->render();
	m_OptionsButton->render();
	m_ExitButton->render();
}

void MainMenuState::dispose()
{
	Logger::info(MAINMENU_TAG, "Dispose");

	delete m_PlayButton;
	delete m_OptionsButton;
	delete m_ExitButton;

	delete s_Instance;
	s_Instance = NULL;
}