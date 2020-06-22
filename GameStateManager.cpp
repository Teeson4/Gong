#include "GameStateManager.h"
#include "Game.h"

GameStateManager* GameStateManager::s_Instance;

void GameStateManager::setState(GameState* gameState)
{
	// Dispose the current GameState
	if (!m_GameStates.empty())
	{
		m_GameStates.back()->dispose();
		m_GameStates.pop_back();
	}

	// Store and initialize the new GameState
	m_GameStates.push_back(gameState);
	m_GameStates.back()->init();
}

void GameStateManager::pushState(GameState* gameState)
{
	// Pause current GameState
	if (!m_GameStates.empty())
	{
		m_GameStates.back()->pause();
	}

	// Store and initialize the new GameState
	m_GameStates.push_back(gameState);
	m_GameStates.back()->init();
}

void GameStateManager::popState()
{
	// Dispose the current GameState
	if (!m_GameStates.empty())
	{
		m_GameStates.back()->dispose();
		m_GameStates.pop_back();
	}

	// Resume previous GameState
	if (!m_GameStates.empty())
	{
		m_GameStates.back()->resume();
	}
}

void GameStateManager::freeState()
{
	// Dispose all GameStates
	while (!m_GameStates.empty())
	{
		m_GameStates.back()->dispose();
		m_GameStates.pop_back();
	}
}

void GameStateManager::input(float delta)
{
	// Handle current GameState events
	m_GameStates.back()->input(delta);
}

void GameStateManager::update(float delta)
{
	// Update current GameState
	m_GameStates.back()->update(delta);
}

void GameStateManager::render()
{
	// Render current GameState
	m_GameStates.back()->render();
}

void GameStateManager::dispose()
{
	// Loop and dispose all GameStates
	if (!m_GameStates.empty())
	{
		for (auto& value : m_GameStates)
		{
			value->dispose();
		}
	}

	delete s_Instance;
	s_Instance = NULL;
}
