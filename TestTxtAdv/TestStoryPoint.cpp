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
    ResponseHandler handler([](const std::string& input) { return true; }, []() {});
    std::vector<ResponseHandler*> handlers;
    handlers.push_back(&handler);

    StoryPoint point;
    REQUIRE(point.GetHandlers().empty());
    point.SetHandlers(handlers);
    REQUIRE(point.GetHandlers().size() == handlers.size());
}