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

bool LuaManager::Exec(const char* filename, const char* funcname)
{
    if (luaL_dofile(L, filename) != LUA_OK)
        return false;

    // Push function onto the stack
    lua_getglobal(L, funcname);
    if (!lua_isfunction(L, -1))
        lua_pop(L, 1); // Pop it back manually

    // No parameters, no return values
    // Pops stack automatically
    return lua_pcall(L, 0, 0, 0) != LUA_OK;
}
