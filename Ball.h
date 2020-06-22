#pragma once

#include "Entity.h"

#include <math.h>

class Ball :
    public Entity
{

private:

    static Ball* s_Instance;

    const float pi = 3.14f;
    const float MAX_BOUNCE_ANGLE = pi / 2;
    const float MAX_NORMAL_INTERSECT = 0.75f;

    float m_Speed;
    const float SPIKE_SPEED = 2100.f;
    const float MAX_SPEED_INCREMENT_SMALL = 100.f;
    const float MAX_SPEED_INCREMENT_BIG = 200.f;
    const float MAX_POINT_INCREMENT = 10;

    bool m_HitPlayer;
    bool m_HitEnemy;

    bool m_ChoosingDirection;
    bool m_Direction;

    int m_Width;
    int m_Height;

public:

    static Ball* instance()
    {
        if (s_Instance == 0)
            s_Instance = new Ball();

        return s_Instance;
    }

    void init();

    void input(float delta);
    void update(float delta);
    void render();

    void dispose();

    inline bool isHitPlayer() const { return m_HitPlayer; }
    inline bool isHitEnemy() const { return m_HitEnemy; }
    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }

};

#define g_Ball Ball::instance()
