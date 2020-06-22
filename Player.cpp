#include "Player.h"
#include "Game.h"

Player* Player::s_Instance;

void Player::init()
{
	m_Width = 20;
	m_Height = 100;

	m_Power = Power::SPIKE;

	m_Position.set(120, (SCREEN_HEIGHT / 2) - (m_Height / 2));
	m_Velocity.clear();

	m_HandleRect.w = (float) m_Width;
	m_HandleRect.h = 25;
	m_HandleRect.x = m_Position.getX();
	m_HandleRect.y = m_Position.getY() + (m_Height / 2) - (m_HandleRect.h / 2);

	m_PaddleRect = { m_Position.getX(), m_Position.getY(), (float) m_Width, (float) m_Height };

	m_OffsetX = 0;

	m_HitAnimationStart = false;
	m_HitAnimationEnd = false;

	m_Score = 0;
	m_Points = 0;

	m_SpikeIdle = false;
	m_SpikeReady = false;
	m_Spiking = false;
}

void Player::input(float delta)
{
	m_Velocity.clear();

	float normJoyLeftY = g_InputManager->getAxis(SDL_CONTROLLER_AXIS_LEFTY) / GAMEPAD_THUMB_MAX;
	float normJoyRightY = g_InputManager->getAxis(SDL_CONTROLLER_AXIS_RIGHTY) / GAMEPAD_THUMB_MAX;
	
	// Up
	if (normJoyLeftY <= -GAMEPAD_LEFT_THUMB_DEADZONE_NORM && m_Position.getY() > 0)
	{
		m_Velocity.setY(normJoyLeftY * MAX_SPEED);
	}

	// Down
	if (normJoyLeftY >= GAMEPAD_LEFT_THUMB_DEADZONE_NORM && m_Position.getY() + m_Height < SCREEN_HEIGHT)
	{
		m_Velocity.setY(normJoyLeftY * MAX_SPEED);
	}

	// Spike ready & ball traveling towards paddle
	if (m_SpikeIdle && g_Ball->m_Velocity.getX() < 0.f)
	{
		if (g_InputManager->getAxis(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) == GAMEPAD_TRIGGER_MAX)
		{
			g_Game->setSlowMode(true);

			m_SpikeReady = true;
		}
	}
	else if (!m_SpikeIdle && g_Ball->m_Velocity.getX() > 0.f)
	{
		g_Game->setSlowMode(false);

		m_SpikeReady = false;
	}

	// Curve ready & ball traveling towards paddle
	if (m_CurveIdle && g_Ball->m_Velocity.getX() < 0.f)
	{
		if (g_InputManager->getAxis(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) == GAMEPAD_TRIGGER_MAX)
		{
			g_Game->setSlowMode(true);

			m_CurveReady = true;
		}
	}
	else if(!m_CurveIdle && g_Ball->m_Velocity.getX() > 0.f)
	{
		g_Game->setSlowMode(false);
	
		m_CurveReady = false;
	}

	if (g_Ball->isHitEnemy() || g_Ball->isHitPlayer())
	{
		m_SpikeReady = false;
		m_CurveReady = false;
	}
}

void Player::update(float delta)
{
	// Able to spike
	if (m_Points >= SPIKE_COST && m_Power == Power::SPIKE)
	{
		m_SpikeIdle = true;
	}
	else
	{
		m_SpikeIdle = false;
	}

	// Able to curve
	if (m_Points >= CURVE_COST && m_Power == Power::CURVE)
	{
		m_CurveIdle = true;
	}
	else
	{
		m_CurveIdle = false;
	}

	if (g_Ball->isHitPlayer())
	{
		m_HitAnimationStart = true;
	}

	if (m_HitAnimationStart)
	{
		if (m_PaddleRect.x < 40)
		{
			m_PaddleRect.x += 1000.f * delta;
			m_OffsetX += 1000.f * delta;
		}
		else
		{
			m_PaddleRect.x = 140;
			m_OffsetX = 20;

			m_HitAnimationStart = false;
			m_HitAnimationEnd = true;
		}
	}

	if (m_HitAnimationEnd)
	{
		if (m_PaddleRect.x > 120)
		{
			m_PaddleRect.x -= 100.f * delta;
			m_OffsetX -= 100.f * delta;
		}
		else
		{
			m_PaddleRect.x = 120;
			m_OffsetX = 0;

			m_HitAnimationEnd = false;
		}
	}

	m_Position.set(m_Position.getX() + (m_Velocity.getX() * delta), m_Position.getY() + (m_Velocity.getY() * delta));

	m_HandleRect.y = m_Position.getY() + (m_Height / 2) - (m_HandleRect.h / 2);

	m_PaddleRect.y = m_Position.getY();
}

void Player::render()
{
	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 0, 149, 255, 255);
	SDL_RenderFillRectF(&g_Game->getRenderer(), &m_HandleRect);

	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRectF(&g_Game->getRenderer(), &m_PaddleRect);

	if (!m_SpikeIdle && !m_SpikeReady && !m_CurveIdle && !m_CurveReady)
	{
		g_AssetManager->render("Resources/Textures/default_hit_graphic.png", m_Position.getX() + m_Width + m_OffsetX, m_Position.getY());
	}
	else if (m_SpikeIdle && !m_SpikeReady)
	{
		g_AssetManager->render("Resources/Textures/spike_graphic_idle.png", m_Position.getX() + m_Width + m_OffsetX, m_Position.getY());
	}
	else if (m_SpikeReady)
	{
		g_AssetManager->render("Resources/Textures/spike_graphic_ready.png", m_Position.getX() + m_Width + m_OffsetX, m_Position.getY());
	}
	else if (m_CurveIdle && !m_CurveReady)
	{
		g_AssetManager->render("Resources/Textures/curve_graphic_idle.png", m_Position.getX() + m_Width + m_OffsetX, m_Position.getY());
	}
	else if (m_CurveReady)
	{
		g_AssetManager->render("Resources/Textures/curve_graphic_ready.png", m_Position.getX() + m_Width + m_OffsetX, m_Position.getY());
	}
}

void Player::dispose()
{

}
