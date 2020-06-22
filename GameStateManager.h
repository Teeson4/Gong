#pragma once

#include <vector>

#include "GameState.h"

#define GSM_TAG "GameStateManager"

class GameState;

class GameStateManager
{

private:

	static GameStateManager* s_Instance;

	std::vector<GameState*> m_GameStates;

public:

	static GameStateManager* instance()
	{
		if (s_Instance == 0)
			s_Instance = new GameStateManager();

		return s_Instance;
	}

	void setState(GameState* gameState);
	void pushState(GameState* gameState);
	void popState();
	void freeState();

	void input(float delta);
	void update(float delta);
	void render();

	void dispose();

};

#define g_GameStateManager GameStateManager::instance()
