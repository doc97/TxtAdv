#include "LuaStoryBranch.h"
#include <iostream>

const char* LuaStoryBranch::className = "LuaStoryBranch";
const Luna<LuaStoryBranch>::FunctionType LuaStoryBranch::methods[] =
{
    { "hello", &LuaStoryBranch::hello },
    {NULL, NULL}
};
const Luna<LuaStoryBranch>::PropertyType LuaStoryBranch::properties[] =
{
    {NULL, NULL}
};

LuaStoryBranch::LuaStoryBranch(lua_State* L)
{
}

LuaStoryBranch::LuaStoryBranch()
{
}

LuaStoryBranch::~LuaStoryBranch()
{
}

void LuaStoryBranch::hello()
{
    std::cout << "Hello!" << std::endl;
}

int LuaStoryBranch::hello(lua_State* L)
{
    hello();
    return 0;
}
