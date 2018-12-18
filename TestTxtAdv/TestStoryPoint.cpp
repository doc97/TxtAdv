#include "catch.hpp"
#include "StoryPoint.h"
#include "ResponseHandler.h"

TEST_CASE("get/set text", "[StoryPoint]")
{
    StoryPoint point;
    REQUIRE(point.GetText() == "");
    point.SetText("a");
    REQUIRE(point.GetText() == "a");
    point.SetText("b");
    REQUIRE(point.GetText() == "b");
}

TEST_CASE("get/set markup text", "[StoryPoint]")
{
    StoryPoint point;

    SECTION("static expressions")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "A"; });
        expr.emplace_back([]() { return "B"; });

        point.SetMarkup("$0", expr);
        REQUIRE(point.GetText() == "A");
        point.SetMarkup("$1", expr);
        REQUIRE(point.GetText() == "B");
    }
    SECTION("dynamic expression")
    {
        std::string var = "a";
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([&var]() { return var; });

        point.SetMarkup("$0", expr);
        REQUIRE(point.GetText() == var);
        var = "b";
        REQUIRE(point.GetText() == var);
    }
    SECTION("invalid expression")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "$0"; });
        point.SetMarkup("$0", expr);
        REQUIRE(point.GetText() == "");
    }
    SECTION("advanced expression")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "1"; });
        expr.emplace_back([]() { return "A"; });
        point.SetMarkup("$$0", expr);
        REQUIRE(point.GetText() == "A");
    }
}

TEST_CASE("get/set handlers", "[StoryPoint]")
{
    std::vector<std::shared_ptr<InputHandler>> handlers;
    handlers.emplace_back(std::make_shared<ResponseHandler>(
        [](const std::string& input) { return true; },
        [](const ResponseMatch& match) {}
    ));
    handlers.emplace_back(std::make_shared<ResponseHandler>(
        [](const std::string& input) { return false; },
        [](const ResponseMatch& match) {}
    ));

    StoryPoint point;
    REQUIRE(point.GetHandlerCount() == 0);
    point.SetHandlers(handlers);
    REQUIRE(point.GetHandlerCount() == handlers.size());
    REQUIRE(point.GetHandlers()[0]->Matches(""));
    REQUIRE(!point.GetHandlers()[1]->Matches(""));
}

TEST_CASE("notify handlers", "[StoryPoint]")
{
    unsigned int flag = 0;
    std::string message = "msg";
    std::vector<std::shared_ptr<InputHandler>> handlers;
    handlers.emplace_back(std::make_shared<ResponseHandler>(
        [](const std::string& input) { return true; },
        [&flag](const ResponseMatch& match) { ++flag; }
    ));
    handlers.emplace_back(std::make_shared<ResponseHandler>(
        [](const std::string& input) { return true; },
        [&flag](const ResponseMatch& match) { ++flag; }
    ));

    StoryPoint point;
    point.NotifyHandlers(message);
    REQUIRE(flag == 0);
    point.SetHandlers(handlers);
    point.NotifyHandlers(message);
    REQUIRE(flag == 2);
}