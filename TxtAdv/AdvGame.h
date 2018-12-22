/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Game.h"
#include "IO.h"
#include "Prompt.h"
#include "ResponseSystem.h"
#include "StoryBranch.h"
#include "GameState.h"
#include "LuaManager.h"

namespace txt
{

class AdvGame : public Game
{
public:
    AdvGame(IO* io);
    ~AdvGame();

    GameState& GetState();
    StoryBranch& GetStory();
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
    LuaManager m_manager;

    void InitLua();
    void InitMisc();
    void InitStory();
    void InitPointOne();
    void InitPointTwo();
    void InitPointThree();
};

} // namespace txt
