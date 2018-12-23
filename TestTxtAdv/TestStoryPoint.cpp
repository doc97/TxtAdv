/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StoryPoint.h"
#include "LambdaResponseHandler.h"

namespace txt
{

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
        point.SetMarkup(expr);

        point.SetText("$0");
        REQUIRE(point.GetText() == "A");
        point.SetText("$1");
        REQUIRE(point.GetText() == "B");
    }
    SECTION("dynamic expression")
    {
        std::string var = "a";
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([&var]() { return var; });
        point.SetMarkup(expr);

        point.SetText("$0");
        REQUIRE(point.GetText() == var);
        var = "b";
        REQUIRE(point.GetText() == var);
    }
    SECTION("invalid expression")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "$0"; });
        point.SetText("$0");
        point.SetMarkup(expr);
        REQUIRE(point.GetText() == "");
    }
    SECTION("advanced expression")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "1"; });
        expr.emplace_back([]() { return "A"; });
        point.SetText("$$0");
        point.SetMarkup(expr);
        REQUIRE(point.GetText() == "A");
    }
}

TEST_CASE("get/set handlers", "[StoryPoint]")
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return true; },
        [](const ResponseMatch& match) {}
    ));
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
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

} // namespace txt
