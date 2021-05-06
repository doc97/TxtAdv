#pragma once

#include "LunaFive.h"
#include <string>

namespace txt
{

template<typename T>
T* GetObj(lua_State* L, int index, const char* className)
{
    luaL_checktype(L, index, LUA_TUSERDATA);
    void* data = luaL_checkudata(L, index, className);
    if (!data)
    {
        luaL_error(L, "Invalid userdata");  // Never returns, 'return nullptr' is redundant
        return nullptr;
    }
    return *(T**)data;  // unbox pointer
}

inline std::string GetString(lua_State* L, int index)
{
    return luaL_checkstring(L, index);
}

inline long long GetLong(lua_State* L, int index)
{
    return luaL_checkinteger(L, index);
}

} // namespace txt
