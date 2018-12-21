#include <iostream>
#include "LuaManager.h"
#include "AdvGame.h"
#include "ConsoleIO.h"
#include "LuaStoryBranch.h"

void runExampleLua()
{
    LuaManager manager;

    std::string err;
    std::vector<LuaParam> params = { { LuaParam::Int, 2LL }, { LuaParam::Int, 2LL } };
    std::vector<LuaParam> retVal = {};
    if (!manager.ExecFunc("LUA/functions.lua", "funcB", params, retVal, err))
        std::cout << err << std::endl;

    std::cin.get();
}

void runExampleGame()
{
    ConsoleIO io;
    AdvGame game(&io);
    game.Run();
}

void runExampleLuna()
{
    LuaManager manager;

    manager.RegisterClass<LuaStoryBranch>();
    manager.PushObject(new LuaStoryBranch, "branch", true);

    std::string err;
    if (!manager.ExecFile("LUA/luna.lua", err))
        std::cout << err << std::endl;

    std::cin.get();
}

int main()
{
    runExampleLuna();
}