#include <stdio.h>

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#include "Callback.h"

void print_error(lua_State* L)
{
    const char* msg = lua_tostring(L, -1);
    puts(msg);
    lua_pop(L, 1);
}

void execute(const char* filename)
{
    lua_State* L = luaL_newstate();

     // Make standard LUA libraries available in the Lua object
    luaL_openlibs(L);

    // Register C functions
    lua_register(L, "hey", hey);

    int result = luaL_loadfile(L, filename);
    if (result != LUA_OK)
    {
        print_error(L);
        return;
    }

    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result != LUA_OK)
    {
        print_error(L);
        return;
    }
}

int main()
{
    execute("LUA/hello.lua");
    execute("LUA/callback.lua");
    getchar();
}