#pragma once

#include "Game.h"
#include "IO.h"
#include "Prompt.h"
#include "ResponseSystem.h"

class AdvGame : public Game
{
public:
    AdvGame(IO* io);
    ~AdvGame();

    void Init() override;
    void Update() override;
    IO* GetIO() const;

private:
    IO* m_io;
    Prompt m_prompt;
    ResponseSystem m_response;
};

