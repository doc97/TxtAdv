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
    handlers.emplace_back([](const std::string& input) { return false; }, []() {});

    StoryPoint point;
    REQUIRE(point.GetHandlerCount() == 0);
    point.SetHandlers(handlers);
    REQUIRE(point.GetHandlerCount() == handlers.size());
    REQUIRE(point.GetHandlers().at(0).GetMatcher()(""));
    REQUIRE(!point.GetHandlers().at(1).GetMatcher()(""));
}

TEST_CASE("notify handlers", "[StoryPoint]")
{
    unsigned int flag = 0;
    std::string message = "msg";
    std::vector<ResponseHandler> handlers;
    handlers.emplace_back([](const std::string& input) { return true; }, [&flag]() { ++flag; });
    handlers.emplace_back([](const std::string& input) { return true; }, [&flag]() { ++flag; });

    StoryPoint point;
    point.NotifyHandlers(message);
    REQUIRE(flag == 0);
    point.SetHandlers(handlers);
    point.NotifyHandlers(message);
    REQUIRE(flag == 2);
}