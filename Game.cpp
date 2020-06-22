#include "Game.h"

// STATIC INSTANCE
// Static instance allows ease of access to other classes.
Game* Game::s_Instance;

Game::Game()
{
	m_Window = NULL;
	m_Renderer = NULL;
	m_Target = NULL;

	m_FadeOut = false;
	m_FadeIn = false;
	m_FadeAlpha = 255;
	m_SlowMode = false;

	m_Running = false;
}

// CREATE SDL, WINDOW, GAME
// Initializes SDL, extentions, etc.
// Uses SDL library to create window.
bool Game::create()
{
	// Initialize SDL | SDL audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		Logger::errorSDL(GAME_TAG, "SDL could not initialize.");
		return false;
	}
	else
	{
		// Load controller mappings
		int numControllers = SDL_GameControllerAddMappingsFromFile("Resources/Mappings/gamecontrollerdb.txt");

		if (numControllers == -1)
		{
			Logger::errorSDL(GAME_TAG, "Could not add mappings from \"gamecontrollerdb.txt\"");
			return false;
		}

		Logger::info(GAME_TAG, "Initialized SDL");

		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			Logger::warning(GAME_TAG, "Linear texture filtering not enabled.");
		}

		// Create Window
		m_Window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_Window == NULL)
		{
			Logger::errorSDL(GAME_TAG, "Window could not be created.");
			return false;
		}
		else
		{
			// Set window parameters
			SDL_SetWindowBordered(m_Window, SDL_FALSE);

			// Create renderer for window
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

			if (m_Renderer == NULL)
			{
				Logger::errorSDL(GAME_TAG, "Renderer could not be created.");
				return false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(m_Renderer, CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;

				// Initialize SDL_image
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					Logger::errorIMG(GAME_TAG, "SDL_image could not be initialized.");
					return false;
				}

				Logger::info(GAME_TAG, "Initialized SDL_image");

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					Logger::errorTTF(GAME_TAG, "SDL_ttf could not be initialized.");
					return false;
				}

				Logger::info(GAME_TAG, "Initialized SDL_ttf");

				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					Logger::errorMIX(GAME_TAG, "SDL_mixer could not be initialized.");
					return false;
				}

				Logger::info(GAME_TAG, "Initialized SDL_mixer");
			}
		}
	}

	m_Target = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_Target == NULL)
	{
		Logger::errorSDL(GAME_TAG, "Unable to create blank texture.");
	}

	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

// INITIALIZATION
// Initializes managers, loads resources.
bool Game::init()
{
	g_AssetManager->loadTexture("Resources/Textures/texture.png");

	// Numbers
	g_NumberRenderer->init();

	// Main Menu Logo
	g_AssetManager->loadTexture("Resources/Textures/main_menu_logo.png");

	// Play Ready Screen
	g_AssetManager->loadTexture("Resources/Textures/play_ready_screen.png");

	// Spike grpahics
	g_AssetManager->loadTexture("Resources/Textures/default_hit_graphic.png");
	g_AssetManager->loadTexture("Resources/Textures/default_hit_graphic_flip.png");
	g_AssetManager->loadTexture("Resources/Textures/spike_graphic_idle.png");
	g_AssetManager->loadTexture("Resources/Textures/spike_graphic_idle_flip.png");
	g_AssetManager->loadTexture("Resources/Textures/spike_graphic_ready.png");
	g_AssetManager->loadTexture("Resources/Textures/spike_graphic_ready_flip.png");
	g_AssetManager->loadTexture("Resources/Textures/spike_graphic.png");
	g_AssetManager->loadTexture("Resources/Textures/curve_graphic.png");
	g_AssetManager->loadTexture("Resources/Textures/power_select.png");
	g_AssetManager->loadTexture("Resources/Textures/curve_graphic_idle.png");
	g_AssetManager->loadTexture("Resources/Textures/curve_graphic_ready.png");

	// Ball
	g_AssetManager->loadTexture("Resources/Textures/ball.png");

	// Buttons
	g_AssetManager->loadTexture("Resources/Textures/play_button_64x18.png");
	g_AssetManager->loadTexture("Resources/Textures/options_button_64x16.png");
	g_AssetManager->loadTexture("Resources/Textures/exit_button_64x16.png");

	// Entry point GameState
	g_GameStateManager->setState(g_MainMenuState);

	// End Initialization
	// Enter game loop
	m_Running = true;

	return true;
}

// INPUT HANDLING
// Ultimately handled inside InputHandler class.
// Polls events, separates into boolean return functions.
void Game::input(float delta)
{
	g_InputManager->updateInput();

	if (g_InputManager->buttonPressed(SDL_CONTROLLER_BUTTON_START))
		g_Game->setRunning(false);

	g_GameStateManager->input(delta);

	g_InputManager->updatePrevInput();
}

// UPDATING STATE
// Handles game logic.
// Update managers.
void Game::update(float delta)
{
	if (m_FadeOut)
	{
		if (m_FadeAlpha - (1000 * delta) < 0)
		{
			m_FadeAlpha = 0;
			
			m_FadeOut = false;
		}
		else
		{
			m_FadeAlpha -= 1000 * delta;
		}
	}

	if (m_FadeIn)
	{
		if (m_FadeAlpha + (1000 * delta) > 255)
		{
			m_FadeAlpha = 255;

			m_FadeIn = false;
		}
		else
		{
			m_FadeAlpha += 1000 * delta;
		}
	}

	g_GameStateManager->update(delta);
}

// RENDERING STATE
// Renders everything onto the screen.
// Render managers.
void Game::render()
{
	SDL_SetRenderTarget(m_Renderer, m_Target);
	SDL_SetRenderDrawColor(m_Renderer, CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
	SDL_RenderClear(m_Renderer);
	// Begin Render

	g_GameStateManager->render();

	// Draw Screen Texture
	SDL_SetTextureColorMod(m_Target, (Uint8) m_FadeAlpha, (Uint8) m_FadeAlpha, (Uint8) m_FadeAlpha);

	SDL_SetRenderTarget(m_Renderer, NULL);
	SDL_RenderCopyEx(m_Renderer, m_Target, NULL, NULL, 0, 0, SDL_FLIP_NONE);

	// End Rendering
	SDL_RenderPresent(m_Renderer);

}

// DISPOSITION OF RESOURCES
// Closes game, disposes resources.
// Cleans up game.
void Game::dispose()
{
	g_AssetManager->dispose();
	g_InputManager->dispose();
	g_GameStateManager->dispose();

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	m_Renderer = NULL;

	SDL_DestroyTexture(m_Target);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	delete s_Instance;
	s_Instance = NULL;
}

// ENCAPSULATED DATA GETTERS / SETTERS
// Provides access to private members.
SDL_Window& Game::getWindow() const
{
	return *m_Window;
}

SDL_Renderer& Game::getRenderer() const
{
	return *m_Renderer;
}

void Game::fadeOut()
{
	m_FadeOut = true;
}

void Game::fadeIn()
{
	m_FadeIn = true;
}

bool Game::isFadingIn()
{
	return m_FadeIn;
}

bool Game::isFadingOut()
{
	return m_FadeOut;
}

bool Game::isRunning() const
{
	return m_Running;
}

void Game::setRunning(bool running)
{
	m_Running = running;
}

bool Game::isSlowMode() const
{
	return m_SlowMode;
}

void Game::setSlowMode(bool slowMode)
{
	m_SlowMode = slowMode;
}
