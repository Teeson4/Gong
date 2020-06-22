#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <ctime>

#include "Logger.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "NumberRenderer.h"

#include "PlayState.h"
#include "MainMenuState.h"

#define GAME_TAG "Game"

static const char* SCREEN_TITLE = "Pong";
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 800;

static const Uint8 CLEAR_R = 24;
static const Uint8 CLEAR_G = 20;
static const Uint8 CLEAR_B = 37;
static const Uint8 CLEAR_A = 255;

class Game
{

private:

	static Game* s_Instance;

	Game();

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Target;

	float m_FadeAlpha;
	bool m_FadeOut;
	bool m_FadeIn;
	bool m_SlowMode;

	bool m_Running;

public:

	static Game* instance()
	{
		if (s_Instance == 0)
			s_Instance = new Game();

		return s_Instance;
	}

	// Initialization Stage
	bool create();
	bool init();

	// Game Loop Stage
	void input(float delta);
	void update(float delta);
	void render();

	// Game Closing Stage
	void dispose();

	// Encapsulation
	SDL_Window& getWindow() const;
	SDL_Renderer& getRenderer() const;

	void fadeIn();
	void fadeOut();

	bool isFadingIn();
	bool isFadingOut();

	bool isRunning() const;
	void setRunning(bool running);

	bool isSlowMode() const;
	void setSlowMode(bool slowMode);

};

#define g_Game Game::instance()
