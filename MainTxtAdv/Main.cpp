#include <iostream>
#include "LuaManager.h"

void exampleLua()
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

int main()
{
    exampleLua();
}