#include <iostream>
#include "LuaManager.h"
#include "AdvGame.h"
#include "ConsoleIO.h"

void runExampleLua()
{
    LuaManager manager;

    std::string err;
    std::vector<LuaParam> params = { { LuaParam::Int, 2LL }, { LuaParam::Int, 2LL } };
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