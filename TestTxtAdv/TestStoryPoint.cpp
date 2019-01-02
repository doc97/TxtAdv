/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StoryPoint.h"
#include "LambdaResponseHandler.h"
#include "LambdaExpression.h"
#include "TxtParser.h"

namespace txt
{

TEST_CASE("StoryPoint - name", "[StoryPoint]")
{
    StoryPoint p1("1");
    REQUIRE(p1.GetName() == "1");
    StoryPoint p2("2");
    REQUIRE(p2.GetName() == "2");
}

TEST_CASE("StoryPoint - get/set text string", "[StoryPoint]")
{
    StoryPoint point("1");
    REQUIRE(point.GetTextStr() == "");
    point.SetTextStr("a");
    REQUIRE(point.GetTextStr() == "a");
    point.SetTextStr("b");
    REQUIRE(point.GetTextStr() == "b");
}

TEST_CASE("StoryPoint - set text parser", "[StoryPoint]")
{
    GameState state;
    StoryPoint point("1");

    SECTION("static expressions")
    {
        std::shared_ptr<TxtParser> parser = std::make_shared<TxtParser>(state);
        parser->AddExpression("a", std::make_unique<LambdaExpression>([]() { return "A"; }));
        parser->AddExpression("b", std::make_unique<LambdaExpression>([]() { return "B"; }));
        point.SetParser(parser);

        point.SetTextStr("{x_a}");
        REQUIRE(point.GetTextStr() == "A");
        point.SetTextStr("{x_b}");
        REQUIRE(point.GetTextStr() == "B");
    }
    SECTION("dynamic expression")
    {
        std::string var = "a";
        std::shared_ptr<TxtParser> parser = std::make_shared<TxtParser>(state);
        parser->AddExpression("0", std::make_unique<LambdaExpression>([&var]() { return var; }));
        point.SetParser(parser);

        point.SetTextStr("{x_0}");
        REQUIRE(point.GetTextStr() == var);
        var = "b";
        REQUIRE(point.GetTextStr() == var);
    }
}

TEST_CASE("StoryPoint - get/set handlers", "[StoryPoint]")
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

    StoryPoint point("1");
    REQUIRE(point.GetHandlerCount() == 0);
    point.SetHandlers(handlers);
    REQUIRE(point.GetHandlerCount() == handlers.size());
    REQUIRE(point.GetHandlers()[0]->Matches(""));
    REQUIRE(!point.GetHandlers()[1]->Matches(""));
}

} // namespace txt
