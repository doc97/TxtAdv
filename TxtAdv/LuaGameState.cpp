/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaGameState.h"
#include "LuaUtils.h"

namespace txt
{

const char* LuaGameState::className = "LuaGameState";
const Luna<LuaGameState>::FunctionType LuaGameState::methods[] =
{
    { "setStr", &LuaGameState::setStr },
    { "getStr", &LuaGameState::getStr },
    { "hasStr", &LuaGameState::hasStr },
    { "setFloat", &LuaGameState::setFloat },
    { "getFloat", &LuaGameState::getFloat },
    { "hasFloat", &LuaGameState::hasFloat },
    { "setInt", &LuaGameState::setInt },
    { "getInt", &LuaGameState::getInt },
    { "hasInt", &LuaGameState::hasInt },
    {NULL, NULL}
};
const Luna<LuaGameState>::PropertyType LuaGameState::properties[] =
{
    {NULL, NULL}
};

LuaGameState::LuaGameState(lua_State* L)
    : m_state(nullptr)
{
}

LuaGameState::LuaGameState(GameState* state)
    : m_state(state)
{
}

LuaGameState::~LuaGameState()
{
}

void LuaGameState::SetStr(const std::string& key, const std::string& value)
{
    m_state->SetString(key, value);
}

std::string LuaGameState::GetStr(const std::string& key)
{
    return m_state->ReadString(key, "");
}

void LuaGameState::SetFloat(const std::string& key, float value)
{
    m_state->SetFloat(key, value);
}

float LuaGameState::GetFloat(const std::string& key)
{
    return m_state->ReadFloat(key, 0.f);
}

void LuaGameState::SetInt(const std::string& key, int value)
{
    m_state->SetInt(key, value);
}

int LuaGameState::GetInt(const std::string& key)
{
    return m_state->ReadInt(key, 0);
}

bool LuaGameState::HasStr(const std::string& key)
{
    return m_state->HasString(key);
}

bool LuaGameState::HasFloat(const std::string& key)
{
    return m_state->HasFloat(key);
}

bool LuaGameState::HasInt(const std::string& key)
{
    return m_state->HasInt(key);
}

/*** LUA INTERFACE ***/

int LuaGameState::setStr(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    const char* val = luaL_checkstring(L, 3);
    s->SetStr(key, val);
    return 0;
}

int LuaGameState::getStr(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    const char* val = s->GetStr(key).c_str();
    lua_pushstring(L, val);
    return 1;
}

int LuaGameState::hasStr(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    bool exists     = s->HasStr(key);
    lua_pushboolean(L, (int)exists);
    return 1;
}

int LuaGameState::setFloat(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    double value    = luaL_checknumber(L, 3);
    s->SetFloat(key, (float)value);
    return 0;
}

int LuaGameState::getFloat(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    float value    = s->GetFloat(key);
    lua_pushnumber(L, (double)value);
    return 1;
}

int LuaGameState::hasFloat(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    bool exists     = s->HasFloat(key);
    lua_pushboolean(L, (int)exists);
    return 1;
}

int LuaGameState::setInt(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    long long value = luaL_checkinteger(L, 3);
    s->SetInt(key, (int)value);
    return 0;
}

int LuaGameState::getInt(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    int value       = s->GetInt(key);
    lua_pushinteger(L, (long long)value);
    return 1;
}

int LuaGameState::hasInt(lua_State* L)
{
    LuaGameState* s = GetObj<LuaGameState>(L, 1, className);
    const char* key = luaL_checkstring(L, 2);
    bool exists     = s->HasInt(key);
    lua_pushboolean(L, (int)exists);
    return 1;
}

} // namespace txt
