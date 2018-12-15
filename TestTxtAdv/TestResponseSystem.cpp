#include "catch.hpp"
#include "ResponseSystem.h"
#include <utility>

TEST_CASE("ResponseHandlers can be added", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("add ResponseHandler as parameter")
    {
        ResponseHandler handler(key, [](){});
        sys.AddHandler(handler);
        REQUIRE(sys.HandlerCount() == 1);
    }
}

TEST_CASE("ResponseHandlers can be removed", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;
    ResponseHandler handler(key, [](){});

    SECTION("remove from empty ResponseSystem")
    {
        sys.RemoveHandler(key);
        REQUIRE(sys.HandlerCount() == 0);
    }
    SECTION("remove from non-empty ResponseSystem")
    {
        sys.AddHandler(handler);
        sys.RemoveHandler(key);
        REQUIRE(sys.HandlerCount() == 0);
    }
}