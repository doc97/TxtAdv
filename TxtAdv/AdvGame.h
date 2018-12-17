#pragma once

#include "Game.h"
#include "IO.h"
#include "Prompt.h"
#include "ResponseSystem.h"
#include "StoryBranch.h"

class AdvGame : public Game
{
public:
    AdvGame(IO* io);
    ~AdvGame();

    void Init() override;
    void Update() override;
    void StoryNext();
    void StoryPrev();
    IO* GetIO() const;

private:
    IO* m_io;
    Prompt m_prompt;
    ResponseSystem m_response;
    StoryBranch m_branch;

    void InitStory();
    void InitPointOne();
    void InitPointTwo();
};

