#include "catch.hpp"
#include "StoryPoint.h"

TEST_CASE("get/set text", "[StoryPoint]")
{
    StoryPoint point;
    REQUIRE(point.GetText() == "");
    point.SetText("a");
    REQUIRE(point.GetText() == "a");
    point.SetText("b");
    REQUIRE(point.GetText() == "b");
}

TEST_CASE("get/set handlers", "[StoryPoint]")
{
    std::vector<ResponseHandler> handlers;
    handlers.emplace_back([](const std::string& input) { return true; }, []() {});

    StoryPoint point;
    REQUIRE(point.GetHandlerCount() == 0);
    point.SetHandlers(handlers);
    REQUIRE(point.GetHandlerCount() == handlers.size());
}