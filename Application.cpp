#include "Game.h"
#include "Timer.h"

#define APP_TAG "Application"

const int FPS = 60;
const int DELAY_TIME = FPS / 1000;

int main(int argc, char* args[])
{

	Timer initTimer;
	initTimer.start();

	if (!g_Game->create())
	{
		Logger::error(APP_TAG, "Failed to create Game.");
	}
	else
	{
		Logger::info(APP_TAG, "Successfully created Game.");

		if (!g_Game->init())
		{
			Logger::error(APP_TAG, "Failed to initialize Game.");
		}
		else
		{
			std::cout << "[Application] (INFO) Done! Successfully initialized in " << initTimer.getTicks() << " ms." << std::endl;

			initTimer.stop();

			float deltaTime = 0;
			Uint32 ticksCount = 0;

			while (g_Game->isRunning())
			{
				if(g_Game->isSlowMode())
					deltaTime = (SDL_GetTicks() - ticksCount) / 3000.f;
				else
					deltaTime = (SDL_GetTicks() - ticksCount) / 1000.f;

				ticksCount = SDL_GetTicks();

				g_Game->input(deltaTime);
				g_Game->update(deltaTime);
				g_Game->render();
			}
		}
	}

	Logger::info(APP_TAG, "Disposing all resources...");

	g_Game->dispose();

	Logger::info(APP_TAG, "Successfully disposed and closed game.");

	return 0;
}
