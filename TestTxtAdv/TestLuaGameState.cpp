/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "LuaGameState.h"

namespace txt
{

TEST_CASE("LuaGameState - configuration", "[LuaGameState]")
{
    REQUIRE(LuaGameState::className == "LuaGameState");
}

TEST_CASE("LuaGameState - registered methods", "[LuaGameState]")
{
    bool hasSetStr = false;
    bool hasGetStr = false;
    bool hasHasStr = false;
    bool hasSetFloat = false;
    bool hasGetFloat = false;
    bool hasHasFloat = false;
    bool hasSetInt = false;
    bool hasGetInt = false;
    bool hasHasInt = false;
    for (size_t i = 0; LuaGameState::methods[i].name; ++i)
    {
        if (LuaGameState::methods[i].name == "setStr")
            hasSetStr = true;
        if (LuaGameState::methods[i].name == "getStr")
            hasGetStr = true;
        if (LuaGameState::methods[i].name == "hasStr")
            hasHasStr = true;
        if (LuaGameState::methods[i].name == "setFloat")
            hasSetFloat = true;
        if (LuaGameState::methods[i].name == "getFloat")
            hasGetFloat = true;
        if (LuaGameState::methods[i].name == "hasFloat")
            hasHasFloat = true;
        if (LuaGameState::methods[i].name == "setInt")
            hasSetInt = true;
        if (LuaGameState::methods[i].name == "getInt")
            hasGetInt = true;
        if (LuaGameState::methods[i].name == "hasInt")
            hasHasInt = true;
    }
    REQUIRE(hasSetStr);
    REQUIRE(hasGetStr);
    REQUIRE(hasHasStr);
    REQUIRE(hasSetFloat);
    REQUIRE(hasGetFloat);
    REQUIRE(hasHasFloat);
    REQUIRE(hasSetInt);
    REQUIRE(hasGetInt);
    REQUIRE(hasHasInt);
}

TEST_CASE("LuaGameState - get/set string", "[LuaGameState]")
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

TEST_CASE("LuaGameState - get/set float", "[LuaGameState]")
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

TEST_CASE("LuaGameState - get/set int", "[LuaGameState]")
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

TEST_CASE("LuaGameState - has string", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(!wrapper.HasStr(key));
    state.SetString(key, "value");
    REQUIRE(wrapper.HasStr(key));
}

TEST_CASE("LuaGameState - has float", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(!wrapper.HasFloat(key));
    state.SetFloat(key, 1.f);
    REQUIRE(wrapper.HasFloat(key));
}

TEST_CASE("LuaGameState - has int", "[LuaGameState]")
{
    std::string key = "key";
    GameState state;
    LuaGameState wrapper(&state);
    REQUIRE(!wrapper.HasInt(key));
    state.SetInt(key, 1);
    REQUIRE(wrapper.HasInt(key));
}

} // namespace txt
