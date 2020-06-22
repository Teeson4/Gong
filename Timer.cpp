#include "Timer.h"

void Timer::start()
{
	m_Started = true;
	m_Paused = false;

	m_StartTicks = SDL_GetTicks();
	m_PausedTicks = 0;
}

void Timer::stop()
{
	m_Started = false;
	m_Paused = false;

	m_StartTicks = 0;
	m_PausedTicks = 0;
}

void Timer::pause()
{
	if (m_Started && !m_Paused)
	{
		m_Paused = true;

		m_PausedTicks = SDL_GetTicks() - m_StartTicks;

		m_StartTicks = 0;
	}
}

void Timer::unpause()
{
	if (m_Started && m_Paused)
	{
		m_Paused = false;

		m_StartTicks = SDL_GetTicks() - m_PausedTicks;

		m_PausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	if (m_Started)
	{
		if (m_Paused)
		{
			time = m_PausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - m_StartTicks;
		}
	}

	return time;
}

bool Timer::isStarted() const
{
	return m_Started;
}

bool Timer::isPaused() const
{
	return m_Paused;
}
