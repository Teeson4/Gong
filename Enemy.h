#pragma once

#include "Entity.h"

class Enemy :
	public Entity
{

private:

    static Enemy* s_Instance;

    int m_Width;
    int m_Height;

    SDL_FRect m_HandleRect;
    SDL_FRect m_PaddleRect;
    float m_OffsetX;

    bool m_HitAnimationStart;
    bool m_HitAnimationEnd;

    float m_Speed;

    const float MAX_SPEED = 900.f;

    int m_Score;
    int m_Hits;

    bool m_SpikeIdle;
    bool m_SpikeReady;
    bool m_Spiking;

public:

    static Enemy* instance()
    {
        if (s_Instance == 0)
            s_Instance = new Enemy();

        return s_Instance;
    }

    void init();

    void input(float delta);
    void update(float delta);
    void render();

    void dispose();

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }

    inline int getScore() const { return m_Score; }
    inline void setScore(int score) { m_Score = score; }

    inline int getHits() const { return m_Hits; }
    inline void setHits(int hits) { m_Hits = hits; }

    inline bool isSpikeIdle() const { return m_SpikeIdle; }
    inline void setSpikeIdle(bool spike) { m_SpikeIdle = spike; }

    inline bool isSpikeReady() const { return m_SpikeReady; }
    inline void setSpikeReady(bool spike) { m_SpikeReady = spike; }

    inline bool isSpiking() const { return m_Spiking; }
    inline void setSpiking(bool spike) { m_Spiking = spike; }

};

#define g_Enemy Enemy::instance()
