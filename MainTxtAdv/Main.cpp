/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include <iostream>
#include "LuaManager.h"
#include "AdvGame.h"
#include "ConsoleIO.h"
#include "LuaStoryBranch.h"

void runExampleLua()
{
    txt::LuaManager manager;

    std::string err;
    std::vector<txt::LuaParam> params = { { txt::LuaParam::Int, 2LL }, { txt::LuaParam::Int, 2LL } };
    std::vector<txt::LuaParam> retVal = {};
    if (!manager.ExecFunc("LUA/functions.lua", "funcB", params, retVal, err))
        std::cout << err << std::endl;

    std::cin.get();
}

void runExampleGame()
{
    txt::ConsoleIO io;
    txt::AdvGame game(&io);
    game.Run();
}

void runExampleLuna()
{
    txt::LuaManager manager;
    txt::StoryBranch branch;

    manager.RegisterClass<txt::LuaStoryBranch>();
    manager.PushObject(new txt::LuaStoryBranch(&branch), "branch", true);

    std::string err;
    if (!manager.ExecFile("LUA/luna.lua", err))
        std::cout << err << std::endl;

    std::cin.get();
}

int main()
{
    runExampleGame();
}