#include "Enemy.h"
#include "Game.h"
#include "Ball.h"

Enemy* Enemy::s_Instance;

void Enemy::init()
{
	m_Width = 20;
	m_Height = 100;

	m_Speed = 0;

	m_Position.set(SCREEN_WIDTH - 120 - m_Width, (SCREEN_HEIGHT / 2) - (m_Height / 2));
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
}

void Enemy::input(float delta)
{

}

void Enemy::update(float delta)
{
	if (g_Ball->isHitEnemy())
	{
		m_Hits++;
	}

	if (m_Hits >= 10)
	{
		m_SpikeIdle = true;
	}

	if (m_Hits >= 11 && !g_Player->isSpikeReady() && g_Ball->m_Velocity.getX() > 0.f && !m_SpikeReady && g_Ball->m_Position.getX() + (g_Ball->getWidth() / 2) >= SCREEN_WIDTH / 2)
	{
		srand((unsigned int) time(NULL));
		int random = rand() % 5;
		if (random == 1 && !m_SpikeReady)
		{
			m_SpikeReady = true;
		}
	}

	if(m_SpikeReady)
		g_Game->setSlowMode(true);

	float destinationY = g_Ball->m_Position.getY() + (g_Ball->getHeight() / 2);

	// If ball is on second half
	if (g_Ball->m_Position.getX() + (g_Ball->getWidth() / 2) >= SCREEN_WIDTH / 2 && g_Ball->m_Velocity.getX() > 0.f)
	{
		if (destinationY < m_Position.getY() + (m_Height / 2))
		{
			m_Speed = -MAX_SPEED;
		}

		if (destinationY > m_Position.getY() + (m_Height / 2))
		{
			m_Speed = MAX_SPEED;
		}
	}
	else
	{
		m_Speed = 0;
	}

	m_Velocity.setY(m_Speed);

	if (m_Position.getY() < 0)
	{
		m_Position.setY(0);
	}

	if (m_Position.getY() + m_Height > SCREEN_HEIGHT)
	{
		m_Position.setY((float) SCREEN_HEIGHT - m_Height);
	}

	// Update Positions
	m_Position.set(m_Position.getX() + (m_Velocity.getX() * delta), m_Position.getY() + (m_Velocity.getY() * delta));

	m_HandleRect.y = m_Position.getY() + (m_Height / 2) - (m_HandleRect.h / 2);

	if (g_Ball->isHitEnemy())
	{
		m_HitAnimationStart = true;
	}

	if (m_HitAnimationStart)
	{
		if (m_PaddleRect.x > 1120)
		{
			m_PaddleRect.x -= 1000.f * delta;
			m_OffsetX -= 1000.f * delta;
		}
		else
		{
			m_PaddleRect.x = 1120;
			m_OffsetX = 20;

			m_HitAnimationStart = false;
			m_HitAnimationEnd = true;
		}
	}

	if (m_HitAnimationEnd)
	{
		if (m_PaddleRect.x < 1140)
		{
			m_PaddleRect.x += 100.f * delta;
			m_OffsetX -= 100.f * delta;
		}
		else
		{
			m_PaddleRect.x = 1140;
			m_OffsetX = 0;

			m_HitAnimationEnd = false;
		}
	}

	m_PaddleRect.y = m_Position.getY();

	m_Velocity.clear();
}

void Enemy::render()
{
	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 255, 0, 68, 255);
	SDL_RenderFillRectF(&g_Game->getRenderer(), &m_HandleRect);

	SDL_SetRenderDrawColor(&g_Game->getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRectF(&g_Game->getRenderer(), &m_PaddleRect);

	if (!m_SpikeIdle && !m_SpikeReady)
	{
		g_AssetManager->render("Resources/Textures/default_hit_graphic_flip.png", m_Position.getX() - g_AssetManager->getTextureWidth("Resources/Textures/default_hit_graphic_flip.png") - m_OffsetX, m_Position.getY());
	}
	else if (m_SpikeIdle && !m_SpikeReady)
	{
		g_AssetManager->render("Resources/Textures/spike_graphic_idle_flip.png", m_Position.getX() - g_AssetManager->getTextureWidth("Resources/Textures/spike_graphic_idle_flip.png") - m_OffsetX, m_Position.getY());
	}
	else
	{
		g_AssetManager->render("Resources/Textures/spike_graphic_ready_flip.png", m_Position.getX() - g_AssetManager->getTextureWidth("Resources/Textures/spike_graphic_ready_flip.png") - m_OffsetX, m_Position.getY());
	}
}

void Enemy::dispose()
{

}
