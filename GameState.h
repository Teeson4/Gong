#pragma once

#include <SDL.h>

class GameState
{

protected:

	GameState() { }

public:

	virtual void init() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void input(float delta) = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;

	virtual void dispose() = 0;

};
