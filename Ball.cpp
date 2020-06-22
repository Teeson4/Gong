#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Ball* Ball::s_Instance;

void Ball::init()
{
	m_Speed = 900.f;
	m_HitPlayer = false;
	m_HitEnemy = false;

	m_Width = g_AssetManager->getTextureWidth("Resources/Textures/ball.png");
	m_Height = g_AssetManager->getTextureHeight("Resources/Textures/ball.png");

	m_Position.set((SCREEN_WIDTH / 2) - (m_Width / 2), (SCREEN_HEIGHT / 2) - (m_Height / 2));
	m_Velocity.setX(-300.f);

	m_ChoosingDirection = true;
	m_Direction = false;
}

void Ball::input(float delta)
{

}

void Ball::update(float delta)
{
	m_HitPlayer = false;
	m_HitEnemy = false;

	if (g_Player->isCurving())
	{
		if (m_ChoosingDirection)
		{
			g_Game->setSlowMode(true);
		}

		if (g_InputManager->getAxis(SDL_CONTROLLER_AXIS_RIGHTY) == GAMEPAD_THUMB_MIN && m_ChoosingDirection)
		{
			m_ChoosingDirection = false;
			m_Direction = false;

			g_Game->setSlowMode(false);
		}

		if (g_InputManager->getAxis(SDL_CONTROLLER_AXIS_RIGHTY) == GAMEPAD_THUMB_MAX && m_ChoosingDirection)
		{
			m_ChoosingDirection = false;
			m_Direction = true;

			g_Game->setSlowMode(false);
		}
	}

	// X AXIS
	// Left Collision
	if (
		(m_Position.getX() <= g_Player->m_Position.getX() + g_Player->getWidth())
		&&
		(m_Position.getX() + m_Width >= g_Player->m_Position.getX())
		&&
		(m_Position.getY() <= g_Player->m_Position.getY() + g_Player->getHeight())
		&&
		(m_Position.getY() + m_Height >= g_Player->m_Position.getY())
		&&
		(m_Velocity.getX() < 0.f)
		)
	{
		float normalizedIntersectY = (((g_Player->m_Position.getY() + (g_Player->getHeight() / 2)) - m_Position.getY()) / (g_Player->getHeight() / 2));
		
		if (normalizedIntersectY > MAX_NORMAL_INTERSECT)
			normalizedIntersectY = MAX_NORMAL_INTERSECT;
		else if (normalizedIntersectY < -MAX_NORMAL_INTERSECT)
			normalizedIntersectY = -MAX_NORMAL_INTERSECT;

		float bounceAngle = normalizedIntersectY * MAX_BOUNCE_ANGLE;

		float speedAmplifier = abs(((g_Player->m_Velocity.getY() / g_Player->MAX_SPEED) * MAX_SPEED_INCREMENT_BIG) + (normalizedIntersectY * MAX_SPEED_INCREMENT_SMALL));

		g_Enemy->setSpiking(false);

		int pointAmount = (int) abs(ceil(normalizedIntersectY * 10));

		if (pointAmount < 6)
			pointAmount = 6;

		// Add points if not spike ready or curving
		if (!g_Player->isSpikeReady() && !g_Player->isCurveReady())
		{
			g_Player->setPoints(g_Player->getPoints() + pointAmount);
		}

		// Remove points if spiking
		if (g_Player->isSpikeReady())
		{
			g_Player->setSpiking(true);

			m_Velocity.set(SPIKE_SPEED * cos(bounceAngle), SPIKE_SPEED * -sin(bounceAngle));

			g_Player->setPoints(g_Player->getPoints() - SPIKE_COST);
		}
		else
		{
			m_Velocity.set((m_Speed + speedAmplifier) * cos(bounceAngle), (m_Speed + speedAmplifier) * -sin(bounceAngle));
		}

		// Remove points if curving
		if (g_Player->isCurveReady())
		{
			g_Player->setCurving(true);

			g_Player->setPoints(g_Player->getPoints() - CURVE_COST);
		}

		// End player stuff

		m_HitPlayer = true;
	}

	// Right Collision
	if (
		(m_Position.getX() + m_Width >= g_Enemy->m_Position.getX())
		&&
		(m_Position.getX() <= g_Enemy->m_Position.getX() + g_Enemy->getWidth())
		&&
		(m_Position.getY() + m_Height >= g_Enemy->m_Position.getY())
		&&
		(m_Position.getY() <= g_Enemy->m_Position.getY() + g_Enemy->getHeight())
		&&
		(m_Velocity.getX() > 0.f)
		)
	{
		float normalizedIntersectY = abs(((g_Enemy->m_Position.getY() + (g_Enemy->getHeight() / 2)) - m_Position.getY()) / (g_Enemy->getHeight() / 2));

		if (normalizedIntersectY > MAX_NORMAL_INTERSECT)
			normalizedIntersectY = MAX_NORMAL_INTERSECT;
		else if (normalizedIntersectY < -MAX_NORMAL_INTERSECT)
			normalizedIntersectY = -MAX_NORMAL_INTERSECT;

		float bounceAngle = normalizedIntersectY * MAX_BOUNCE_ANGLE;

		float speedAmplifier = abs(((g_Player->m_Velocity.getY() / g_Player->MAX_SPEED) * MAX_SPEED_INCREMENT_BIG) + (normalizedIntersectY * MAX_SPEED_INCREMENT_SMALL));

		m_ChoosingDirection = true;

		g_Player->setSpiking(false);
		g_Player->setCurving(false);

		if (g_Enemy->isSpikeReady())
		{
			g_Enemy->setSpiking(true);
			g_Enemy->setSpikeReady(false);
			g_Enemy->setSpikeIdle(false);
			g_Enemy->setHits(0);

			/*if (normalizedIntersectY < 0.f)
				m_Velocity.set(-SPIKE_SPEED, 200.f);
			else if (normalizedIntersectY > 0.f)
				m_Velocity.set(-SPIKE_SPEED, -200.f);*/

			m_Velocity.set(SPIKE_SPEED * cos(bounceAngle), SPIKE_SPEED * -sin(bounceAngle));
		}
		else
		{
			m_Velocity.set((m_Speed + speedAmplifier) * cos(bounceAngle) * -1, (m_Speed + speedAmplifier) * -sin(bounceAngle));
		}

		m_HitEnemy = true;
	}

	// Y AXIS
	// Top Collision
	if (m_Position.getY() <= 0 && m_Velocity.getY() < 0.f)
	{
		m_Velocity.setY(m_Velocity.getY() * -1);
	}

	// Bottom Collision
	if (m_Position.getY() + m_Height > SCREEN_HEIGHT && m_Velocity.getY() > 0.f)
	{
		m_Velocity.setY(m_Velocity.getY() * -1);
	}

	// OUT OF BOUNDS
	// Player score
	if (m_Position.getX() >= SCREEN_WIDTH)
	{
		g_Player->setScore(g_Player->getScore() + 1);
		g_Enemy->setHits(0);

		g_Player->setSpiking(false);
		g_Enemy->setSpikeIdle(false);
		g_Enemy->setSpikeReady(false);

		g_Player->setCurving(false);

		m_Position.set((SCREEN_WIDTH / 2) - (m_Width / 2), (SCREEN_HEIGHT / 2) - (m_Height / 2));
		m_Velocity.set(300.f, 0.f);
	}

	// Ai score
	if (m_Position.getX() + m_Width <= 0)
	{
		g_Enemy->setScore(g_Enemy->getScore() + 1);
		g_Player->setPoints(0);

		g_Enemy->setSpiking(false);

		m_Position.set((SCREEN_WIDTH / 2) - (m_Width / 2), (SCREEN_HEIGHT / 2) - (m_Height / 2));
		m_Velocity.set(-300.f, 0.f);
	}

	// Curving ball
	if (!m_ChoosingDirection && !m_Direction && g_Player->isCurving())
	{
		
	}

	if (!m_ChoosingDirection && m_Direction && g_Player->isCurving())
	{
		
	}

	m_Position.set(m_Position.getX() + (m_Velocity.getX() * delta), m_Position.getY() + (m_Velocity.getY() * delta));
}

void Ball::render()
{
	SDL_SetTextureColorMod(g_AssetManager->getTexture("Resources/Textures/ball.png"), 255, 255, 255);

	if (g_Player->isSpikeReady() && m_Position.getY() >= g_Player->m_Position.getY() && m_Position.getY() + m_Height <= g_Player->m_Position.getY() + g_Player->getHeight() || g_Player->isSpiking())
	{
		SDL_SetTextureColorMod(g_AssetManager->getTexture("Resources/Textures/ball.png"), 255, 0, 68);
	}

	if (g_Player->isCurveReady() && m_Position.getY() >= g_Player->m_Position.getY() && m_Position.getY() + m_Height <= g_Player->m_Position.getY() + g_Player->getHeight() || g_Player->isCurving())
	{
		SDL_SetTextureColorMod(g_AssetManager->getTexture("Resources/Textures/ball.png"), 254, 174, 52);
	}

	if (g_Enemy->isSpikeReady() && m_Position.getY() >= g_Enemy->m_Position.getY() && m_Position.getY() + m_Height <= g_Enemy->m_Position.getY() + g_Enemy->getHeight() || g_Enemy->isSpiking())
	{
		SDL_SetTextureColorMod(g_AssetManager->getTexture("Resources/Textures/ball.png"), 255, 0, 68);
	}

	g_AssetManager->render("Resources/Textures/ball.png", m_Position.getX(), m_Position.getY());
}

void Ball::dispose()
{

}
