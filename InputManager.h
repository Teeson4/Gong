#pragma once

#include <SDL.h>
#include <string>

#include "Game.h"
#include "Vector2.h"

#define INPUT_TAG "InputManager"
#define GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define GAMEPAD_LEFT_THUMB_DEADZONE_NORM 0.23953978087
#define GAMEPAD_RIGHT_THUMB_DEADZONE_NORM 0.26517532883
#define GAMEPAD_THUMB_MAX            32767
#define GAMEPAD_THUMB_MIN           -32768
#define GAMEPAD_TRIGGER_THRESHOLD    30
#define GAMEPAD_TRIGGER_MAX          32767

enum class MOUSE_BUTTON
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2,
	BACK = 3,
	FORWARD = 4
};

class InputManager
{

private:

	static InputManager* s_Instance;

	// Controller
	SDL_GameController* m_GameController;
	int m_WhichController;

	Uint8 m_ButtonStates[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 m_ButtonStatesPrev[SDL_CONTROLLER_BUTTON_MAX];
	float m_AxisValues[SDL_CONTROLLER_AXIS_MAX];

	// Mouse
	Vector2* m_MousePosition;

	Uint32 m_PrevMouseState;
	Uint32 m_MouseState;

	// Keyboard
	Uint8* m_PrevKeyboardState;
	const Uint8* m_KeyboardState;
	int m_KeyLength;

public:

	static InputManager* instance()
	{
		if (s_Instance == 0)
			s_Instance = new InputManager();

		return s_Instance;
	}

	InputManager();

	// Update all inputs
	void updateInput();
	void updatePrevInput();

	// Poll controller events
	bool buttonDown(SDL_GameControllerButton button);
	bool buttonUp(SDL_GameControllerButton button);
	bool buttonPressed(SDL_GameControllerButton button);
	bool buttonReleased(SDL_GameControllerButton button);
	float getAxis(SDL_GameControllerAxis axis);

	// Poll mouse events
	Vector2& getMousePosition() const;

	bool mouseDown(MOUSE_BUTTON  button);
	bool mouseUp(MOUSE_BUTTON  button);

	bool mousePressed(MOUSE_BUTTON  button);
	bool mouseReleased(MOUSE_BUTTON  button);

	// Poll keyboard events
	bool keyDown(SDL_Scancode scanCode);
	bool keyUp(SDL_Scancode scanCode);

	bool keyPressed(SDL_Scancode scanCode);
	bool keyReleased(SDL_Scancode scanCode);

	// Dispose of anything
	void dispose();

};

#define g_InputManager InputManager::instance()
