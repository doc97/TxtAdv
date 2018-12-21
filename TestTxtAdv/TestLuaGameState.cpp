#include "catch.hpp"
#include "LuaGameState.h"

TEST_CASE("configuration", "[LuaGameState]")
{
    REQUIRE(LuaGameState::className == "LuaGameState");
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(!wrapper.isExisting);
    REQUIRE(!wrapper.isPrecious);
}

TEST_CASE("registered methods", "[LuaGameState]")
{
    bool hasSetStr = false;
    bool hasGetStr = false;
    bool hasSetFloat = false;
    bool hasGetFloat = false;
    bool hasSetInt = false;
    bool hasGetInt = false;
    for (size_t i = 0; LuaGameState::methods[i].name; ++i)
    {
        if (LuaGameState::methods[i].name == "setStr")
            hasSetStr = true;
        if (LuaGameState::methods[i].name == "getStr")
            hasGetStr = true;
        if (LuaGameState::methods[i].name == "setFloat")
            hasSetFloat = true;
        if (LuaGameState::methods[i].name == "getFloat")
            hasGetFloat = true;
        if (LuaGameState::methods[i].name == "setInt")
            hasSetInt = true;
        if (LuaGameState::methods[i].name == "getInt")
            hasGetInt = true;
    }
    REQUIRE(hasSetStr);
    REQUIRE(hasGetStr);
    REQUIRE(hasSetFloat);
    REQUIRE(hasGetFloat);
    REQUIRE(hasSetInt);
    REQUIRE(hasGetInt);
}

TEST_CASE("get/set string", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(wrapper.GetStr(key) == "");
    state.SetString(key, "valueA");
    REQUIRE(wrapper.GetStr(key) == "valueA");
    state.SetString(key, "valueB");
    REQUIRE(wrapper.GetStr(key) == "valueB");
}

TEST_CASE("get/set float", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(wrapper.GetFloat(key) == 0.f);
    state.SetFloat(key, 1.f);
    REQUIRE(wrapper.GetFloat(key) == 1.f);
    state.SetFloat(key, 2.f);
    REQUIRE(wrapper.GetFloat(key) == 2.f);
}

TEST_CASE("get/set int", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(wrapper.GetInt(key) == 0);
    state.SetInt(key, 1);
    REQUIRE(wrapper.GetInt(key) == 1);
    state.SetInt(key, 2);
    REQUIRE(wrapper.GetInt(key) == 2);
}
