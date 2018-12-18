#pragma once

#include "Game.h"
#include "IO.h"
#include "Prompt.h"
#include "ResponseSystem.h"
#include "StoryBranch.h"
#include "GameState.h"

class AdvGame : public Game
{
public:
    AdvGame(IO* io);
    ~AdvGame();

    void StoryNext();
    void StoryPrev();
    GameState& GetState();
    IO* GetIO() const;
protected:
    void Init() override;
    void Update() override;
private:
    IO* m_io;
    Prompt m_prompt;
    ResponseSystem m_response;
    StoryBranch m_branch;
    GameState m_state;

    void InitStory();
    void InitPointOne();
    void InitPointTwo();
};

