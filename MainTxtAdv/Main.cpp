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
    if (!manager.Exec("LUA/functions.lua", "funcB", params, retVal, err))
        std::cout << err << std::endl;

    getchar();
}

void runExampleGame()
{
    ConsoleIO io;
    AdvGame game(&io);
    game.Run();
}

void runExampleLuna()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    Luna<LuaStoryBranch>::Register(L);

    LuaStoryBranch branch;
    Luna<LuaStoryBranch>::new_global(L, &branch, "branch");

    if (luaL_dofile(L, "LUA/luna.lua") != LUA_OK)
    {
        const char* msg = lua_tostring(L, -1);
        lua_pop(L, 1);
        printf_s(msg);
    }
    lua_close(L);
    getchar();
}

int main()
{
    runExampleLuna();
}