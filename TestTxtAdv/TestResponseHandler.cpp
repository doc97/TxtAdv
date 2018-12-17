#include "catch.hpp"
#include "ResponseHandler.h"
#include <string>

TEST_CASE("ResponseHandler")
{
    std::string key = "key";
    bool isHandled = false;
    std::function<bool(const std::string&)> matcher = [key](const std::string& input) { return input == key; };
    ResponseHandler handler(matcher, [&isHandled]() { isHandled = true; });

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

