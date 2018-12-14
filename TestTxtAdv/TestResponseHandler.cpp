#include "catch.hpp"
#include "ResponseHandler.h"
#include <string>

TEST_CASE("InputHandler")
{
    bool isHandled = false;
    std::string key = "a";
    ResponseHandler handler(key, [&isHandled]() { isHandled = true; });

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

