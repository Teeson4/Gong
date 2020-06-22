#include "InputManager.h"

InputManager* InputManager::s_Instance;

// INITIALIZATION
// Initialize variables
InputManager::InputManager()
{	
	// Controller
	m_GameController = NULL;
	m_WhichController = -1;

	memset(m_ButtonStates, 0, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);
	memset(m_ButtonStatesPrev, 0, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);
	memset(m_AxisValues, 0, sizeof(Uint8) * SDL_CONTROLLER_AXIS_MAX);

	// Mouse
	m_MousePosition = new Vector2();

	m_MouseState = NULL;
	m_PrevMouseState = NULL;

	// Keyboard
	m_KeyboardState = SDL_GetKeyboardState(&m_KeyLength);
	m_PrevKeyboardState = new Uint8[m_KeyLength];
	
	memcpy(m_PrevKeyboardState, m_KeyboardState, m_KeyLength);
}

// INPUT HANDLING STATE
// Update all inputs in PollEvent loop
// Switch case event types
void InputManager::updateInput()
{
	// Update Controller
	if (m_GameController != NULL)
	{
		SDL_GameControllerUpdate();

		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		{
			m_ButtonStates[i] = SDL_GameControllerGetButton(m_GameController, (SDL_GameControllerButton) i);
		}

		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
		{
			m_AxisValues[i] = SDL_GameControllerGetAxis(m_GameController, (SDL_GameControllerAxis) i);
		}
	}

	// Update Mouse
	int mouseX, mouseY;
	m_MouseState = SDL_GetMouseState(&mouseX, &mouseY);
	m_MousePosition->set(mouseX, mouseY);

	// Poll Events
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			g_Game->setRunning(false);
		}
		else if (event.type == SDL_JOYDEVICEADDED)
		{
			if (m_GameController == NULL)
			{
				m_WhichController = event.cdevice.which;
				m_GameController = SDL_GameControllerOpen(m_WhichController);

				memset(m_ButtonStates, 0, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);
				memset(m_ButtonStatesPrev, 0, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);
				memset(m_AxisValues, 0, sizeof(Uint8) * SDL_CONTROLLER_AXIS_MAX);

				Logger::info(INPUT_TAG, "Controller connected!");
			}
		}
		else if (event.type == SDL_JOYDEVICEREMOVED)
		{
			if(m_WhichController == event.cdevice.which)
			{
				m_WhichController = -1;
				m_GameController = NULL;

				Logger::info(INPUT_TAG, "Controller disconnected! Please reconnect.");
			}
		}
	}
}

void InputManager::updatePrevInput()
{
	if (m_GameController != NULL)
	{
		memcpy(&m_ButtonStatesPrev, &m_ButtonStates, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);
	}

	memcpy(m_PrevKeyboardState, m_KeyboardState, m_KeyLength);

	m_PrevMouseState = m_MouseState;
}

// CONTROLLER EVENTS
// Controller Axis and buttons
bool InputManager::buttonDown(SDL_GameControllerButton button)
{
	return m_ButtonStates[button] == 1;
}

bool InputManager::buttonUp(SDL_GameControllerButton button)
{
	return m_ButtonStates[button] == 0;
}

bool InputManager::buttonPressed(SDL_GameControllerButton button)
{
	return m_ButtonStates[button] == 1 && m_ButtonStatesPrev[button] == 0;
}

bool InputManager::buttonReleased(SDL_GameControllerButton button)
{
	return m_ButtonStates[button] == 0 && m_ButtonStatesPrev[button] == 1;
}

float InputManager::getAxis(SDL_GameControllerAxis axis)
{
	return m_AxisValues[axis];
}

// MOUSE EVENTS
// Mouse motion, buttons pressed
Vector2& InputManager::getMousePosition() const
{
	return *m_MousePosition;
}

bool InputManager::mouseDown(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTON::LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTON::MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTON::RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTON::BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTON::FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return (m_MouseState & mask);
}

bool InputManager::mouseUp(MOUSE_BUTTON  button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTON::LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTON::MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTON::RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTON::BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTON::FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return !(m_MouseState & mask);
}

bool InputManager::mousePressed(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTON::LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTON::MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTON::RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTON::BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTON::FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return !(m_PrevMouseState & mask) && (m_MouseState & mask);
}

bool InputManager::mouseReleased(MOUSE_BUTTON  button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTON::LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTON::MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTON::RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTON::BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTON::FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return (m_PrevMouseState & mask) && !(m_MouseState & mask);
}

// KEYBOARD EVENTS
// Keys down, up
bool InputManager::keyDown(SDL_Scancode scanCode)
{
	return m_KeyboardState[scanCode];
}

bool InputManager::keyUp(SDL_Scancode scanCode)
{
	return !m_KeyboardState[scanCode];
}

bool InputManager::keyPressed(SDL_Scancode scanCode)
{
	return !m_PrevKeyboardState[scanCode] && m_KeyboardState[scanCode];
}

bool InputManager::keyReleased(SDL_Scancode scanCode)
{
	return m_PrevKeyboardState[scanCode] && !m_KeyboardState[scanCode];
}

// DISPOSITION STATE
// Dispose of all resources allocated
void InputManager::dispose()
{
	SDL_GameControllerClose(m_GameController);

	m_MousePosition->clear();
	delete m_MousePosition;
	m_MousePosition = NULL;

	delete[] m_PrevKeyboardState;
	m_PrevKeyboardState = NULL;

	delete s_Instance;
	s_Instance = NULL;
}
