#include "catch.hpp"
#include "ResponseSystem.h"
#include <utility>

TEST_CASE("ResponseHandlers can be added", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("add ResponseHandler as parameter")
    {
        ResponseHandler handler([&key](const std::string& input) { return input == key; },
            [](const ResponseMatch& match) {});
        sys.AddHandler(handler);
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add ResponseHandler by parameters")
    {
        sys.AddHandler([&key](const std::string& input) { return input == key; },
            [](const ResponseMatch& match) {});
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add multiple ResponseHandlers")
    {
        std::vector<ResponseHandler> handlers;
        handlers.emplace_back([](const std::string& input) { return false; }, [](const ResponseMatch& match) {});
        handlers.emplace_back([](const std::string& input) { return false; }, [](const ResponseMatch& match) {});
        sys.AddHandlers(handlers);
        REQUIRE(sys.HandlerCount() == 2);
    }
}

TEST_CASE("ResponseHandlers can be removed", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;
    ResponseHandler handler([&key](const std::string& input) { return input == key; },
        [](const ResponseMatch& match) {});

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

TEST_CASE("Remove all ResponseHandlers")
{
    ResponseSystem sys;
    ResponseHandler handlerA([](const std::string& input) { return input == "a"; },
        [](const ResponseMatch& match) {});
    ResponseHandler handlerB([](const std::string& input) { return input == "b"; },
        [](const ResponseMatch& match) {});

    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
    sys.AddHandler(handlerA);
    sys.AddHandler(handlerB);
    REQUIRE(sys.HandlerCount() == 2);
    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
}