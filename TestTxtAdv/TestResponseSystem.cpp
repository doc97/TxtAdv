#include "catch.hpp"
#include "ResponseSystem.h"
#include <utility>

TEST_CASE("ResponseHandlers can be added", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("add ResponseHandler as parameter")
    {
        ResponseHandler handler([&key](const std::string& input) { return input == key; }, []() {});
        sys.AddHandler(handler);
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add ResponseHandler by parameters")
    {
        sys.AddHandler([&key](const std::string& input) { return input == key; }, []() {});
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add multiple ResponseHandlers")
    {
        std::vector<ResponseHandler> handlers;
        handlers.emplace_back([](const std::string& input) { return false; }, []() {});
        handlers.emplace_back([](const std::string& input) { return false; }, []() {});
        sys.AddHandlers(handlers);
        REQUIRE(sys.HandlerCount() == 2);
    }
}

TEST_CASE("ResponseHandlers can be removed", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;
    ResponseHandler handler([&key](const std::string& input) { return input == key; }, []() {});

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
    ResponseHandler handlerA([](const std::string& input) { return input == "a"; }, []() {});
    ResponseHandler handlerB([](const std::string& input) { return input == "b"; }, []() {});

    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
    sys.AddHandler(handlerA);
    sys.AddHandler(handlerB);
    REQUIRE(sys.HandlerCount() == 2);
    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
}