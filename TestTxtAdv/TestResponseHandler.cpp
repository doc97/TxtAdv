#include "catch.hpp"
#include "ResponseHandler.h"
#include <string>

typedef std::function<ResponseMatch(const std::string&)> MatchFunc;

TEST_CASE("matcher function", "[ResponseHandler]")
{
    ResponseHandler trueHandler([](const std::string& input) { return ResponseMatch(true); }, []() {});
    ResponseHandler falseHandler([](const std::string& input) { return ResponseMatch(false); }, []() {});
    REQUIRE(trueHandler.GetMatcher()("").IsMatch());
    REQUIRE(!falseHandler.GetMatcher()("").IsMatch());
}

TEST_CASE("action function", "[ResponseHandler]")
{
    std::string key = "key";
    bool isHandled = false;
    MatchFunc matcher = [&key](const std::string& input) { return input == key; };
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
