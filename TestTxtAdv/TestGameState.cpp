#include "catch.hpp"
#include "GameState.h"

TEST_CASE("has state", "[GameState]")
{
    std::string key = "key";
    GameState state;
    REQUIRE(!state.HasInt(key));
    REQUIRE(!state.HasFloat(key));
    REQUIRE(!state.HasString(key));

    SECTION("integer state")
    {
        state.SetInt(key, 1);
        REQUIRE(state.HasInt(key));
    }
    SECTION("float state")
    {
        state.SetFloat(key, 1.f);
        REQUIRE(state.HasFloat(key));
    }
    SECTION("string state")
    {
        state.SetString(key, "1");
        REQUIRE(state.HasString(key));
    }
}

TEST_CASE("read integer state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("read non-existent state")
    {
        REQUIRE(state.ReadInt(key, -1) == -1);
        REQUIRE(state.ReadInt(key, 0) == 0);
        REQUIRE(state.ReadInt(key, 1) == 1);
    }
    SECTION("read existing value")
    {
        state.SetInt(key, 1);
        REQUIRE(state.ReadInt(key, -1) == 1);
        state.SetInt(key, 2);
        REQUIRE(state.ReadInt(key, -1) == 2);
    }
}

TEST_CASE("get integer state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("get non-existent state")
    {
        REQUIRE(!state.HasInt(key));
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
        REQUIRE(state.HasInt(key));
        REQUIRE(state.GetInt(key) == 1);
    }
}

TEST_CASE("get all integer states", "[GameState]")
{
    size_t count = 10;
    GameState state;
    REQUIRE(state.GetAllInts().size() == 0);
    for (size_t i = 0; i < count; ++i)
        state.SetInt(std::to_string(i), i);

    std::unordered_map<std::string, int> map = state.GetAllInts();
    REQUIRE(map.size() == count);
    for (size_t i = 0; i < count; ++i)
        REQUIRE(map[std::to_string(i)] == i);
}

TEST_CASE("update integer state", "[GameState]")
{
    std::string key = key;
    GameState state;

    SECTION("update non-existent state")
    {
        try
        {
            state.UpdateInt(key, 1);
            FAIL("Trying to update non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument) {}
    }
    SECTION("update existing state")
    {
        state.SetInt(key, 1);
        try
        {
            state.UpdateInt(key, 2);
            REQUIRE(state.GetInt(key) == 2);
            state.UpdateInt(key, 3);
            REQUIRE(state.GetInt(key) == 3);
        }
        catch (std::invalid_argument)
        {
            FAIL("Updating existing state should NOT throw std::invalid_argument");
        }
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
            REQUIRE(state.HasInt(key));
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

TEST_CASE("read float state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("read non-existent state")
    {
        REQUIRE(state.ReadFloat(key, -1.f) == -1.f);
        REQUIRE(state.ReadFloat(key, 0.f) == 0.f);
        REQUIRE(state.ReadFloat(key, 1.f) == 1.f);
    }
    SECTION("read existing state")
    {
        state.SetFloat(key, 1.f);
        REQUIRE(state.ReadFloat(key, -1.f) == 1.f);
        state.SetFloat(key, 2.f);
        REQUIRE(state.ReadFloat(key, -1.f) == 2.f);
    }
}

TEST_CASE("get float state", "[GameState]")
{
    std::string key = "a";
    GameState state;

    SECTION("get non-existent state")
    {
        REQUIRE(!state.HasFloat(key));
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
        REQUIRE(state.HasFloat(key));
        REQUIRE(state.GetFloat(key) == 1.5f);
    }
}

TEST_CASE("get all float states", "[GameState]")
{
    size_t count = 10;
    GameState state;
    REQUIRE(state.GetAllFloats().size() == 0);
    for (size_t i = 0; i < count; ++i)
        state.SetFloat(std::to_string(i), (float) i);

    std::unordered_map<std::string, float> map = state.GetAllFloats();
    REQUIRE(map.size() == count);
    for (size_t i = 0; i < count; ++i)
        REQUIRE(map[std::to_string(i)] == (float) i);
}

TEST_CASE("update float state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("update non-existent state")
    {
        try
        {
            state.UpdateFloat(key, 1.f);
            FAIL("Trying to update non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument) {}
    }
    SECTION("update existing state")
    {
        state.SetFloat(key, 1.f);
        try
        {
            state.UpdateFloat(key, 2.f);
            REQUIRE(state.GetFloat(key) == 2.f);
            state.UpdateFloat(key, 3.f);
            REQUIRE(state.GetFloat(key) == 3.f);
        }
        catch (std::invalid_argument)
        {
            FAIL("Updating existing state should NOT throw std::invalid_argument");
        }
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
            REQUIRE(state.HasFloat(key));
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

TEST_CASE("read string state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("read non-existent state")
    {
        REQUIRE(state.ReadString(key, "a") == "a");
        REQUIRE(state.ReadString(key, "b") == "b");
        REQUIRE(state.ReadString(key, "c") == "c");
    }
    SECTION("read existing value")
    {
        state.SetString(key, "d");
        REQUIRE(state.ReadString(key, "a") == "d");
        state.SetString(key, "e");
        REQUIRE(state.ReadString(key, "a") == "e");
    }
}

TEST_CASE("get string state", "[GameState]")
{
    std::string key = "a";
    GameState state;

    SECTION("get non-existent state")
    {
        REQUIRE(!state.HasString(key));
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
        REQUIRE(state.HasString(key));
        REQUIRE(state.GetString(key) == "a");
    }
}

TEST_CASE("get all string states", "[GameState]")
{
    size_t count = 10;
    GameState state;
    REQUIRE(state.GetAllStrings().size() == 0);
    for (size_t i = 0; i < count; ++i)
        state.SetString(std::to_string(i), std::to_string(i));

    std::unordered_map<std::string, std::string> map = state.GetAllStrings();
    REQUIRE(map.size() == count);
    for (size_t i = 0; i < count; ++i)
        REQUIRE(map[std::to_string(i)] == std::to_string(i));
}

TEST_CASE("update string state", "[GameState]")
{
    std::string key = "key";
    GameState state;

    SECTION("update non-existent state")
    {
        try
        {
            state.UpdateString(key, "a");
            FAIL("Trying to update non-existent state should throw std::invalid_argument");
        }
        catch (std::invalid_argument) {}
    }
    SECTION("update existing state")
    {
        state.SetString(key, "a");
        try
        {
            state.UpdateString(key, "b");
            REQUIRE(state.GetString(key) == "b");
            state.UpdateString(key, "c");
            REQUIRE(state.GetString(key) == "c");
        }
        catch (std::invalid_argument)
        {
            FAIL("Updating existing state should NOT throw std::invalid_argument");
        }
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
            REQUIRE(state.HasString(key));
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
    REQUIRE(!state.HasInt(iKey));
    REQUIRE(!state.HasFloat(fKey));
    REQUIRE(!state.HasString(sKey));

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
