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

    if (luaL_loadfile(L, filename) != LUA_OK)
    {
        print_error(L);
        return;
    }

    // LUA_MULTRET => All return values are pushed onto the stack
    if (lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK)
    {
        print_error(L);
        return;
    }
}

void exec_fn(const char* filename, const char* funcname)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, filename) != LUA_OK)
    {
        print_error(L);
        return;
    }

    // Push function onto the stack
    lua_getglobal(L, funcname);
    if (!lua_isfunction(L, -1))
    {
        // Pop it back manually
        lua_pop(L, 1);
        return;
    }

    // No parameters, no return values
    // Pops stack automatically
    if (lua_pcall(L, 0, 0, 0) != LUA_OK)
        print_error(L);
}

int main()
{
    execute("LUA/hello.lua");
    exec_fn("LUA/functions.lua", "funcA");
    getchar();
}