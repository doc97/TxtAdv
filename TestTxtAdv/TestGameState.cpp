#include "catch.hpp"
#include "GameState.h"

TEST_CASE("get integer state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("get non-existent state")
    {
        try
        {
            state.GetInt(key);
            FAIL("Trying to access non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument)
        {
        }
    }
    SECTION("get existing state")
    {
        state.SetInt(key, 1);
        REQUIRE(state.GetInt(key) == 1);
    }
}

TEST_CASE("set integer state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    for (int i = -10; i < 10; ++i)
    {
        SECTION("value " + std::to_string(i))
        {
            state.SetInt(key, i);
            REQUIRE(state.GetInt(key) == i);
        }
    }

    SECTION("set existing state")
    {
        state.SetInt(key, 1);
        state.SetInt(key, 2);
        REQUIRE(state.GetInt(key) == 2);
    }
}

TEST_CASE("get float state", "[GameState]")
{
    std::string key = "a";
    GameState state;

    SECTION("get non-existent state")
    {
        try
        {
            state.GetFloat(key);
            FAIL("Trying to access non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument)
        {
        }
    }
    SECTION("get existing state")
    {
        state.SetFloat(key, 1.5f);
        REQUIRE(state.GetFloat(key) == 1.5f);
    }
}

TEST_CASE("set float state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    for (float i = -10.5f; i < 10.5f; ++i)
    {
        SECTION("value " + std::to_string(i))
        {
            state.SetFloat(key, i);
            REQUIRE(state.GetFloat(key) == i);
        }
    }

    SECTION("set existing state")
    {
        state.SetFloat(key, 1.5f);
        state.SetFloat(key, 2.5f);
        REQUIRE(state.GetFloat(key) == 2.5f);
    }
}

TEST_CASE("get string state", "[GameState]")
{
    std::string key = "a";
    GameState state;

    SECTION("get non-existent state")
    {
        try
        {
            state.GetString(key);
            FAIL("Trying to access non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument)
        {
        }
    }
    SECTION("get existing state")
    {
        state.SetString(key, "a");
        REQUIRE(state.GetString(key) == "a");
    }
}

TEST_CASE("set string state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    for (char c = 'a'; c < 'g'; ++c)
    {
        std::string value(1, c);
        SECTION("value " + value)
        {
            state.SetString(key, value);
            REQUIRE(state.GetString(key) == value);
        }
    }
}

TEST_CASE("reset state", "[GameState]")
{
    std::string iKey = "i_1";
    std::string fKey = "f_1";
    std::string sKey = "s_1";
    GameState state;
    state.SetInt(iKey, 1);
    state.SetFloat(fKey, 1.f);
    state.SetString(sKey, "1");

    state.Reset();

    try
    {
        state.GetInt(iKey);
        FAIL("Trying to access non-existent state should throw std::invalid_argument");
    }
    catch (std::invalid_argument) {}

    try
    {
        state.GetFloat(fKey);
        FAIL("Trying to access non-existent state should throw std::invalid_argument");
    }
    catch (std::invalid_argument) {}

    try
    {
        state.GetString(sKey);
        FAIL("Trying to access non-existent state should throw std::invalid_argument");
    }
    catch (std::invalid_argument) {}
}
