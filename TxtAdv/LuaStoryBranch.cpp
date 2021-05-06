/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaStoryBranch.h"
#include "LuaUtils.h"

namespace txt
{

const char* LuaStoryBranch::className = "LuaStoryBranch";
const Luna<LuaStoryBranch>::FunctionType LuaStoryBranch::methods[] =
{
    { "next", &LuaStoryBranch::next },
    { "prev", &LuaStoryBranch::prev },
    { "head", &LuaStoryBranch::head },
    { "setHead", &LuaStoryBranch::setHead },
    { "setHeadByName", &LuaStoryBranch::setHeadByName },
    { "isAtStart", &LuaStoryBranch::isAtStart },
    { "isAtEnd", &LuaStoryBranch::isAtEnd },
    {NULL, NULL}
};
const Luna<LuaStoryBranch>::PropertyType LuaStoryBranch::properties[] =
{
    {NULL, NULL}
};

LuaStoryBranch::LuaStoryBranch(lua_State* L)
    : m_branch(nullptr)
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

int LuaStoryBranch::Head()
{
    return m_branch->Head();
}

void LuaStoryBranch::SetHead(unsigned int index)
{
    m_branch->SetHead(index);
}

void LuaStoryBranch::SetHeadByName(const std::string& name)
{
    m_branch->SetHeadByName(name);
}

bool LuaStoryBranch::IsAtStart()
{
    return m_branch->IsAtStart();
}

bool LuaStoryBranch::IsAtEnd()
{
    return m_branch->IsAtEnd();
}

/*** LUA INTERFACE ***/

int LuaStoryBranch::next(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    b->Next();
    return 0;
}

int LuaStoryBranch::prev(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    b->Prev();
    return 0;
}

int LuaStoryBranch::head(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    lua_pushinteger(L, b->Head());
    return 1;
}

int LuaStoryBranch::setHead(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    long long idx = GetLong(L, 2);
    b->SetHead(static_cast<unsigned int>(idx));
    return 0;
}

int LuaStoryBranch::setHeadByName(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    std::string name = GetString(L, 2);
    b->SetHeadByName(name);
    return 0;
}

int LuaStoryBranch::isAtStart(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    lua_pushboolean(L, b->IsAtStart());
    return 1;
}

int LuaStoryBranch::isAtEnd(lua_State* L)
{
    LuaStoryBranch* b = GetObj<LuaStoryBranch>(L, 1, className);
    lua_pushboolean(L, b->IsAtEnd());
    return 1;
}

} // namespace txt
