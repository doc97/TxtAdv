/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include"LuaResponseHandler.h"

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

namespace txt
{

int luaValue = 0;
int luaApply(lua_State* L)
{
    luaValue = 1;
    return 0;
}

static const luaL_Reg testlib[] =
{
    { "handle", &luaApply }
};

TEST_CASE("LuaResponseHandler - set manager", "[LuaResponseHandler]")
{
    LuaManager manager;
    LuaResponseHandler handler("LUA/test.lua", "matches_true");
    try
    {
        handler.Matches("");
        FAIL("Without having specified a LuaManager, the LuaResponseHandler should throw a std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
    handler.SetManager(&manager);
    REQUIRE(handler.Matches(""));
}

TEST_CASE("LuaResponseHandler - lua matcher function", "[LuaResponseHandler]")
{
    LuaManager manager;
    LuaResponseHandler trueHandler(&manager, "LUA/test.lua", "matches_true");
    LuaResponseHandler falseHandler(&manager, "LUA/test.lua", "matches_false");
    REQUIRE(trueHandler.Matches(""));
    REQUIRE(!falseHandler.Matches(""));
}

TEST_CASE("LuaResponseHandler - lua action function", "[LuaResponseHandler]")
{
    luaValue = 0;
    std::string key = "key";
    LuaManager manager;
    LuaResponseHandler handler(&manager, "LUA/test.lua", "matches_key", "action_handle");
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

TEST_CASE("LuaResponseHandler - lua action lib function", "[LuaResponseHandler]")
{
    luaValue = 0;
    std::string key = "key";
    LuaManager manager;
    LuaResponseHandler handler(&manager, "LUA/test.lua", "matches_key", "action_lib_handle");
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

} // namespace txt
