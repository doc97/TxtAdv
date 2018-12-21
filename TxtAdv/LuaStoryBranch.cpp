#include "LuaStoryBranch.h"

const char* LuaStoryBranch::className = "LuaStoryBranch";
const Luna<LuaStoryBranch>::FunctionType LuaStoryBranch::methods[] =
{
    { "next", &LuaStoryBranch::next },
    { "prev", &LuaStoryBranch::prev },
    {NULL, NULL}
};
const Luna<LuaStoryBranch>::PropertyType LuaStoryBranch::properties[] =
{
    {NULL, NULL}
};

LuaStoryBranch::LuaStoryBranch(lua_State* L)
{
}

LuaStoryBranch::LuaStoryBranch(StoryBranch* branch)
    : m_branch(branch)
{
}

LuaStoryBranch::~LuaStoryBranch()
{
}

void LuaStoryBranch::Next()
{
    m_branch->Next();
}

void LuaStoryBranch::Prev()
{
    m_branch->Prev();
}

/*** LUA INTERFACE ***/

int LuaStoryBranch::next(lua_State* L)
{
    LuaStoryBranch* b = GetObj(L, 1);
    b->Next();
    return 0;
}

int LuaStoryBranch::prev(lua_State* L)
{
    LuaStoryBranch* b = GetObj(L, 1);
    b->Prev();
    return 0;
}

LuaStoryBranch* LuaStoryBranch::GetObj(lua_State* L, int index)
{
    luaL_checktype(L, index, LUA_TUSERDATA);
    void* data = luaL_checkudata(L, index, className);
    if (!data)
    {
        luaL_error(L, "Invalid userdata");  // Never returns, 'return nullptr' is redundant
        return nullptr;
    }
    return *(LuaStoryBranch**)data;  // unbox pointer
}
