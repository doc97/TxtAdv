#pragma once

#include "LunaFive.h"
#include "StoryBranch.h"

class LuaStoryBranch
{
public:
    LuaStoryBranch();
    ~LuaStoryBranch();
    void hello();

    // Lua interface
    static const char* className;
    static const Luna<LuaStoryBranch>::FunctionType methods[];
    static const Luna<LuaStoryBranch>::PropertyType properties[];

    bool isExisting = false;
    bool isPrecious = false;

    LuaStoryBranch(lua_State* L);
    int hello(lua_State* L);
};

