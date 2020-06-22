#pragma once

#include <SDL.h>
#include <iostream>

#include "Logger.h"
#include "Vector2.h"

class Entity
{

public:

	Vector2 m_Position;
	Vector2 m_Velocity;

	virtual void input(float delta) = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;

	virtual void dispose() = 0;

};
