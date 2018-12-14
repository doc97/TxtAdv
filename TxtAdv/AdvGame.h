#pragma once

#include "Game.h"
#include "Prompt.h"
#include "InputHandler.h"
#include "IO.h"

class AdvGame : public Game
{
public:
    AdvGame(IO* io);
    ~AdvGame();

    void Init() override;
    void Update() override;

private:
    Prompt m_prompt;
    InputHandler m_handler;
};

