#include "LuaGameState.h"

const char* LuaGameState::className = "LuaStoryBranch";
const Luna<LuaGameState>::FunctionType LuaGameState::methods[] =
{
    { "setStr", &LuaGameState::setStr },
    {NULL, NULL}
};
const Luna<LuaGameState>::PropertyType LuaGameState::properties[] =
{
    {NULL, NULL}
};

LuaGameState::LuaGameState(lua_State* L)
{
}

LuaGameState::LuaGameState(GameState* state)
    : m_state(state)
{
}

LuaGameState::~LuaGameState()
{
}

void LuaGameState::setStr(const std::string& key, const std::string& value)
{
    m_state->SetString(key, value);
}

int LuaGameState::setStr(lua_State* L)
{
    LuaGameState* s = GetObj(L, 1);
    const char* key = luaL_checkstring(L, 2);
    const char* val = luaL_checkstring(L, 3);
    s->setStr(key, val);
    return 0;
}

LuaGameState* LuaGameState::GetObj(lua_State* L, int index)
{
    luaL_checktype(L, index, LUA_TUSERDATA);
    void* data = luaL_checkudata(L, index, className);
    if (!data)
    {
        luaL_error(L, "Invalid userdata");  // Never returns, 'return nullptr' is redundant
        return nullptr;
    }
    return *(LuaGameState**)data;  // unbox pointer
}
