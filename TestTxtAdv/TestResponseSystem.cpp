#include "catch.hpp"
#include "ResponseSystem.h"

TEST_CASE("ResponseHandlers can be added", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("add ResponseHandler by parameters")
    {
        sys.AddResponseHandler(
            [&key](const std::string& input) { return ResponseMatch(input == key); },
            [](const ResponseMatch& match) {}
        );
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add Handler by pointer")
    {
        ResponseHandler handler(
            [&key](const std::string& input) { return ResponseMatch(input == key); },
            [](const ResponseMatch& match) {}
        );
        sys.AddHandler(std::make_shared<ResponseHandler>(handler));
        REQUIRE(sys.HandlerCount() == 1);
    }
}

TEST_CASE("ResponseHandlers can be removed", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("remove from empty ResponseSystem")
    {
        sys.RemoveHandler(key);
        REQUIRE(sys.HandlerCount() == 0);
    }
    SECTION("remove from non-empty ResponseSystem")
    {
        sys.AddResponseHandler(
            [&key](const std::string& input) { return input == key; },
            [](const ResponseMatch& match) {}
        );
        sys.AddResponseHandler(
            [&key](const std::string& input) { return input != key; },
            [](const ResponseMatch& match) {}
        );
        sys.RemoveHandler(key);
        REQUIRE(sys.HandlerCount() == 1);
    }
}

TEST_CASE("Remove all ResponseHandlers")
{
    ResponseSystem sys;

    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
    sys.AddResponseHandler(
        [](const std::string& input) { return input == "a"; },
        [](const ResponseMatch& match) {}
    );
    sys.AddResponseHandler(
        [](const std::string& input) { return input == "b"; },
        [](const ResponseMatch& match) {}
    );
    REQUIRE(sys.HandlerCount() == 2);
    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
}