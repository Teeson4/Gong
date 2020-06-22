#pragma once

#include "Entity.h"

const int SPIKE_COST = 10;
const int CURVE_COST = 10;

enum class Power
{
    SPIKE,
    NONE,
    CURVE
};

class Player :
    public Entity
{

private:

    static Player* s_Instance;

    int m_Width;
    int m_Height;

    Power m_Power;

    SDL_FRect m_HandleRect;
    SDL_FRect m_PaddleRect;
    float m_OffsetX;

    bool m_HitAnimationStart;
    bool m_HitAnimationEnd;

    int m_Score;
    int m_Points;

    bool m_SpikeIdle;
    bool m_SpikeReady;
    bool m_Spiking;

    bool m_CurveIdle;
    bool m_CurveReady;
    bool m_Curving;

public:

    const float MAX_SPEED = 800.f;

    static Player* instance()
    {
        if (s_Instance == 0)
            s_Instance = new Player();

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

    inline int getPoints() const { return m_Points; }
    inline void setPoints(int points) { m_Points = points; }

    inline bool isSpikeIdle() const { return m_SpikeIdle; }
    inline void setSpikeIdle(bool idle) { m_SpikeIdle = true; }

    inline bool isSpikeReady() const { return m_SpikeReady; }
    inline void setSpikeReady(bool ready) { m_SpikeReady = true; }

    inline bool isSpiking() const { return m_Spiking; }
    inline void setSpiking(bool spiking) { m_Spiking = spiking; }

    inline bool isCurveIdle() const { return m_CurveIdle; }
    inline void setCurveIdle(bool idle) { m_CurveIdle = idle; }

    inline bool isCurveReady() const { return m_CurveReady; }
    inline void setCurveReady(bool ready) { m_CurveReady = ready; }

    inline bool isCurving() const { return m_Curving; }
    inline void setCurving(bool curving) { m_Curving = curving; }

    inline Power getPower() const { return m_Power; }
    inline void setPower(Power power) { m_Power = power; }

};

#define g_Player Player::instance()
