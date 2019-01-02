/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StoryBranch.h"
#include "LambdaResponseHandler.h"
#include "LambdaExpression.h"
#include "TxtParser.h"

namespace txt
{

TEST_CASE("StoryBranch - get head", "[StoryBranch]")
{
    StoryBranch branch;

    SECTION("nullpointer point")
    {
        REQUIRE(branch.GetHead() == nullptr);
    }
    SECTION("one point")
    {
        StoryPoint point("1");
        point.SetTextStr("text");
        branch.AddPoint(point);
        REQUIRE(branch.GetHead()->GetTextStr() == point.GetTextStr());

        SECTION("another point")
        {
            StoryPoint point2("2");
            point2.SetTextStr("text2");
            branch.AddPoint(point2);
            REQUIRE(branch.GetHead()->GetTextStr() == point.GetTextStr());
        }
    }
}

TEST_CASE("StoryBranch - set head", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", "1", {}, {});
    branch.AddPoint("2", "2", {}, {});
    branch.AddPoint("3", "3", {}, {});

    SECTION("normal")
    {
        branch.SetCurrentPoint(1);
        REQUIRE(branch.GetHead()->GetTextStr() == "2");
    }
    SECTION("out of range")
    {
        try
        {
            branch.SetCurrentPoint(3);
            FAIL("Trying to set index out of range should throw std::out_of_range");
        }
        catch (std::out_of_range) {}
    }
}

TEST_CASE("StoryBranch - add points", "[StoryBranch]")
{
    StoryBranch branch;
    REQUIRE(branch.Length() == 0);
    REQUIRE(branch.Empty());

    SECTION("add one point")
    {
        StoryPoint point("1");
        point.SetTextStr("text");
        branch.AddPoint(point);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetTextStr() == point.GetTextStr());

        SECTION("add another point")
        {
            StoryPoint point2("2");
            point2.SetTextStr("text2");
            branch.AddPoint(point2);
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetTextStr() == point.GetTextStr());
            REQUIRE(branch.GetPointAt(1)->GetTextStr() == point2.GetTextStr());
        }
    }
    SECTION("add point by text")
    {
        std::string text1 = "text";
        branch.AddPoint("1", text1, {}, {});
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetTextStr() == text1);

        SECTION("add another point")
        {
            std::string text2 = "text2";
            branch.AddPoint("2", text2, {}, {});
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetTextStr() == text1);
            REQUIRE(branch.GetPointAt(1)->GetTextStr() == text2);
        }
    }
    SECTION("add point by markup")
    {
        GameState state;
        state.SetString("b", "B");
        std::shared_ptr<TxtParser> parser = std::make_shared<TxtParser>(state);
        parser->AddExpression("a", std::make_unique<LambdaExpression>([]() { return "A"; }));

        branch.AddPoint("a", "text {x_a}", parser, {});
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetTextStr() == "text A");
        branch.AddPoint("b", "text {s_b}", parser, {});
        REQUIRE(branch.Length() == 2);
        REQUIRE(branch.GetPointAt(1)->GetTextStr() == "text B");
    }
    SECTION("add point by text and handlers")
    {
        std::vector<std::shared_ptr<ResponseHandler>> handlers1;
        handlers1.emplace_back(std::make_shared<LambdaResponseHandler>(
            [](const std::string& input) { return true; },
            [](const ResponseMatch& match) {}
        ));
        std::string text1 = "text";
        branch.AddPoint("1", text1, {}, handlers1);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetTextStr() == text1);
        REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == handlers1.size());

        SECTION("add another point")
        {
            std::vector<std::shared_ptr<ResponseHandler>> handlers2;
            handlers2.emplace_back(std::make_shared<LambdaResponseHandler>(
                [](const std::string& input) { return false; },
                [](const ResponseMatch& match) {}
            ));
            std::string text2 = "text2";
            branch.AddPoint("2", text2, {}, handlers2);
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetTextStr() == text1);
            REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == handlers1.size());
            REQUIRE(branch.GetPointAt(1)->GetTextStr() == text2);
            REQUIRE(branch.GetPointAt(1)->GetHandlerCount() == handlers2.size());
        }
    }
    SECTION("add point by markup and handlers")
    {
        GameState state;
        state.SetString("b", "B");
        std::shared_ptr<TxtParser> parser = std::make_shared<TxtParser>(state);
        parser->AddExpression("a", std::make_unique<LambdaExpression>([]() { return "A"; }));

        std::vector<std::shared_ptr<ResponseHandler>> handlers;
        handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
            [](const std::string& input) { return false; },
            [](const ResponseMatch& match) {}
        ));

        branch.AddPoint("a", "text {x_a}", parser, handlers);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetTextStr() == "text A");
        REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == 1);
        branch.AddPoint("b", "text {s_b}", parser, handlers);
        REQUIRE(branch.Length() == 2);
        REQUIRE(branch.GetPointAt(1)->GetTextStr() == "text B");
        REQUIRE(branch.GetPointAt(1)->GetHandlerCount() == 1);
    }
}

TEST_CASE("StoryBranch - next point", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", "1", {}, {});
    branch.AddPoint("2", "2", {}, {});
    branch.AddPoint("3", "3", {}, {});

    REQUIRE(branch.GetHead()->GetTextStr() == "1");
    branch.Next();
    REQUIRE(branch.GetHead()->GetTextStr() == "2");
    branch.Next();
    REQUIRE(branch.GetHead()->GetTextStr() == "3");
    branch.Next();
    REQUIRE(branch.GetHead()->GetTextStr() == "3");
}

TEST_CASE("StoryBranch - previous point", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", "1", {}, {});
    branch.AddPoint("2", "2", {}, {});
    branch.AddPoint("3", "3", {}, {});
    branch.Next();
    branch.Next();

    REQUIRE(branch.GetHead()->GetTextStr() == "3");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetTextStr() == "2");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetTextStr() == "1");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetTextStr() == "1");

}

TEST_CASE("StoryBranch - parent branch", "[StoryBranch]")
{
    StoryBranch parent;
    StoryBranch branch;
    REQUIRE(branch.GetParentBranch() == nullptr);
    branch.SetParentBranch(parent);
    REQUIRE(branch.GetParentBranch() != nullptr);
    branch.UnsetParentBranch();
    REQUIRE(branch.GetParentBranch() == nullptr);
}

TEST_CASE("StoryBranch - branch name", "[StoryBranch]")
{
    SECTION("empty name")
    {
        StoryBranch branch;
        REQUIRE(branch.GetName() == "");
    }
    SECTION("non-empty name")
    {
        StoryBranch branch("a");
        REQUIRE(branch.GetName() == "a");
    }
}

} // namespace txt
