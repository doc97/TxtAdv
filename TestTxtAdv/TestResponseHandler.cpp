#include "catch.hpp"
#include "ResponseHandler.h"
#include <string>

TEST_CASE("matcher function", "[ResponseHandler]")
{
    std::function<bool(const std::string&)> trueMatcher = [](const std::string& input) { return true; };
    std::function<bool(const std::string&)> falseMatcher = [](const std::string& input) { return false; };
    ResponseHandler trueHandler(trueMatcher, []() {});
    ResponseHandler falseHandler(falseMatcher, []() {});
    REQUIRE(trueHandler.GetMatcher()(""));
    REQUIRE(!falseHandler.GetMatcher()(""));
}

TEST_CASE("action function", "[ResponseHandler]")
{
    std::string key = "key";
    bool isHandled = false;
    std::function<bool(const std::string&)> matcher = [&key](const std::string& input) { return input == key; };
    std::function<void()> action = [&isHandled]() { isHandled = true; };
    ResponseHandler handler(matcher, action);

    SECTION("matching key")
    {
        handler.HandleInput(key);
        REQUIRE(isHandled);

    }
    SECTION("non-matching key")
    {
        handler.HandleInput("b");
        REQUIRE(!isHandled);
    }
}
