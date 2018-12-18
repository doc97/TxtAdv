#include <iostream>
#include "LuaManager.h"
#include "AdvGame.h"
#include "ConsoleIO.h"

void runExampleLua()
{
    LuaManager manager;

    std::string err;
    std::vector<LuaParam> params;
    params.emplace_back(LuaParam::Int, (void*)2);
    params.emplace_back(LuaParam::Int, (void*)3);
    if (!manager.Exec("LUA/functions.lua", "funcB", params, err))
        std::cout << err << std::endl;

    getchar();
}

void runExampleGame()
{
    ConsoleIO io;
    AdvGame game(&io);
    game.Run();
}

int main()
{
    runExampleLua();
}