#include "catch.hpp"
#include"LuaResponseHandler.h"

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

int luaValue;
int luaApply(lua_State* L)
{
    luaValue = 1;
    return 0;
}

static const luaL_Reg testlib[] =
{
    { "handle", &luaApply }
};

TEST_CASE("lua matcher function", "[LuaResponseHandler]")
{
    LuaManager manager;
    LuaResponseHandler trueHandler(&manager, "LUA/true.lua");
    LuaResponseHandler falseHandler(&manager, "LUA/false.lua");
    REQUIRE(trueHandler.Matches(""));
    REQUIRE(!falseHandler.Matches(""));
}

TEST_CASE("lua action function", "[LuaResponseHandler]")
{
    luaValue = 0;
    std::string key = "key";
    LuaManager manager;
    LuaResponseHandler handler(&manager, "LUA/action.lua");
    manager.RegisterFunc("handle", &luaApply);

    SECTION("matching key")
    {
        handler.HandleInput(key);
        REQUIRE(luaValue == 1);
    }
    SECTION("non-matching key")
    {
        handler.HandleInput("b");
        REQUIRE(luaValue == 0);
    }
}

TEST_CASE("lua action lib function", "[LuaResponseHandler]")
{
    luaValue = 0;
    std::string key = "key";
    LuaManager manager;
    LuaResponseHandler handler(&manager, "LUA/actionlib.lua");
    manager.RegisterLib("test", testlib, 1);

    SECTION("matching key")
    {
        handler.HandleInput(key);
        REQUIRE(luaValue == 1);
    }
    SECTION("non-matching key")
    {
        handler.HandleInput("b");
        REQUIRE(luaValue == 0);
    }
}