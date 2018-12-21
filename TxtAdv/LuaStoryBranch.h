#pragma once

#include "LunaFive.h"
#include "StoryBranch.h"

class LuaStoryBranch
{
public:
    LuaStoryBranch(StoryBranch* branch);
    ~LuaStoryBranch();
    void Next();
    void Prev();

    // Lua interface
    static const char* className;
    static const Luna<LuaStoryBranch>::FunctionType methods[];
    static const Luna<LuaStoryBranch>::PropertyType properties[];

    bool isExisting = false;
    bool isPrecious = false;

    LuaStoryBranch(lua_State* L);
    int next(lua_State* L);
    int prev(lua_State* L);
private:
    StoryBranch* m_branch = nullptr;

    static LuaStoryBranch* GetObj(lua_State* L, int index);
};

