#pragma once

#include <SDL.h>

class Timer
{

private:

	Uint32 m_StartTicks;
	Uint32 m_PausedTicks;

	bool m_Started;
	bool m_Paused;

public:

	Timer() : m_StartTicks(0), m_PausedTicks(0), m_Started(false), m_Paused(false) {}

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted() const;
	bool isPaused() const;

};
