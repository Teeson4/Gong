#pragma once

#include "GameState.h"
#include "Game.h"
#include "Logger.h"
#include "Vector2.h"

#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

#define PLAY_TAG "PlayState"

class PlayState :
    public GameState
{

private:

    static PlayState* s_Instance;

    SDL_Rect m_PlayerScoreRect;
    SDL_Rect m_AiScoreRect;
    SDL_Rect m_CenterLineRect;

    bool m_FirstHit;
    bool m_ReadyToPlay;
    bool m_TriggerMainMenuState;

    float m_UiAlphaFade;

public:

    static PlayState* instance()
    {
        if (s_Instance == 0)
            s_Instance = new PlayState();

        return s_Instance;
    }

    void init();
    
    void pause();
    void resume();

    void input(float delta);
    void update(float delta);
    void render();

    void dispose();

};

#define g_PlayState PlayState::instance()
