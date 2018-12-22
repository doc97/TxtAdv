/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#ifdef __cplusplus
extern "C"
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

int hey(lua_State* L)
{
    int args = lua_gettop(L);
    printf("hey() was called with %d arguments:\n", args);
    
    for (int i = 1; i <= args; ++i)
        printf("  arg %d '%s'\n'", i, lua_tostring(L, i));

    // push return value on top of the stack
    lua_pushnumber(L, 123);

    // number of return values returned
    return 1;
}