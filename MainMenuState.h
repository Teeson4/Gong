#pragma once

#include "GameState.h"
#include "Button.h"

#include <vector>

#define MAINMENU_TAG "MainMenuState"

class MainMenuState :
    public GameState
{

private:

    static MainMenuState* s_Instance;

    int m_Choice;
    const int MIN_CHOICE = 0;
    const int MAX_CHOICE = 2;

    SDL_Rect m_Background1, m_Background2;

    Button *m_PlayButton, *m_OptionsButton, *m_ExitButton;

    bool m_TriggerPlayState, m_TriggerOptionsState;

public:

    static MainMenuState* instance()
    {
        if (s_Instance == 0)
            s_Instance = new MainMenuState();

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

#define g_MainMenuState MainMenuState::instance()
