#pragma once

#include "Game.h"
#include "Prompt.h"
#include "ResponseSystem.h"
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
    ResponseSystem m_response;
};

