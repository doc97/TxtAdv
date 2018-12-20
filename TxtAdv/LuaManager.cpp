#include "LuaManager.h"

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

LuaManager::LuaManager()
{
    Init();
}

LuaManager::~LuaManager()
{
    lua_close(L);
}

LuaManager& LuaManager::operator=(const LuaManager& other)
{
    if (this != &other)
    {
        lua_State* newL = luaL_newstate();
        lua_close(L);
        L = newL;
    }
    return *this;
}

void LuaManager::Reset()
{
    lua_close(L);
    Init();
}

void LuaManager::Init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
}

void LuaManager::GetError(std::string& error)
{
    const char* msg = lua_tostring(L, -1);
    lua_pop(L, 1);
    if (msg)
        error.assign(msg);
}

bool LuaManager::Exec(const char* filename, const char* funcname, const std::vector<LuaParam>& params,
    std::string& error)
{
    if (luaL_dofile(L, filename) != LUA_OK)
    {
        GetError(error);
        return false;
    }

    // Push function onto the stack
    lua_getglobal(L, funcname);
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1); // Pop it back manually
        error = std::string("ERROR: '" + std::string(funcname) + "' is not the name of any known function!");
        return false;
    }

    LoadParams(params);

    // Pops stack automatically
    if (lua_pcall(L, params.size(), 0, 0) != LUA_OK)
    {
        GetError(error);
        return false;
    }
    return true;
}

void LuaManager::LoadParams(const std::vector<LuaParam>& params)
{
    for (const LuaParam& p : params)
        LoadParam(p);
}

void LuaManager::LoadParam(const LuaParam& param)
{
    switch (param.type)
    {
    case LuaParam::Bool: lua_pushboolean(L, param.data.b); break;
    case LuaParam::Int: lua_pushinteger(L, param.data.i); break;
    case LuaParam::Double: lua_pushnumber(L, param.data.d); break;
    case LuaParam::String: lua_pushstring(L, param.data.s); break;
    }
}
