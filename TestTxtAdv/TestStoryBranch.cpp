#include "catch.hpp"
#include "StoryBranch.h"
#include "LambdaResponseHandler.h"

TEST_CASE("get head", "[StoryBranch]")
{
    StoryBranch branch;

    SECTION("nullpointer point")
    {
        REQUIRE(branch.GetHead() == nullptr);
    }
    SECTION("one point")
    {
        StoryPoint point;
        point.SetText("text");
        branch.AddPoint(point);
        REQUIRE(branch.GetHead()->GetText() == point.GetText());

        SECTION("another point")
        {
            StoryPoint point2;
            point2.SetText("text2");
            branch.AddPoint(point2);
            REQUIRE(branch.GetHead()->GetText() == point.GetText());
        }
    }
}

TEST_CASE("set head", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", {}, {});
    branch.AddPoint("2", {}, {});
    branch.AddPoint("3", {}, {});

    SECTION("normal")
    {
        branch.SetCurrentPoint(1);
        REQUIRE(branch.GetHead()->GetText() == "2");
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

TEST_CASE("add points", "[StoryBranch]")
{
    StoryBranch branch;
    REQUIRE(branch.Length() == 0);
    REQUIRE(branch.Empty());

    SECTION("add one point")
    {
        StoryPoint point;
        point.SetText("text");
        branch.AddPoint(point);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetText() == point.GetText());

        SECTION("add another point")
        {
            StoryPoint point2;
            point2.SetText("text2");
            branch.AddPoint(point2);
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetText() == point.GetText());
            REQUIRE(branch.GetPointAt(1)->GetText() == point2.GetText());
        }
    }
    SECTION("add point by text")
    {
        std::string text1 = "text";
        branch.AddPoint(text1, {}, {});
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetText() == text1);

        SECTION("add another point")
        {
            std::string text2 = "text2";
            branch.AddPoint(text2, {}, {});
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetText() == text1);
            REQUIRE(branch.GetPointAt(1)->GetText() == text2);
        }
    }
    SECTION("add point by markup")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "A"; });
        expr.emplace_back([]() { return "B"; });

        branch.AddPoint("text $0", expr, {});
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetText() == "text A");
        branch.AddPoint("text $1", expr, {});
        REQUIRE(branch.Length() == 2);
        REQUIRE(branch.GetPointAt(1)->GetText() == "text B");
    }
    SECTION("add point by text and handlers")
    {
        std::vector<std::shared_ptr<ResponseHandler>> handlers1;
        handlers1.emplace_back(std::make_shared<LambdaResponseHandler>(
            [](const std::string& input) { return true; },
            [](const ResponseMatch& match) {}
        ));
        std::string text1 = "text";
        branch.AddPoint(text1, {}, handlers1);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetText() == text1);
        REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == handlers1.size());

        SECTION("add another point")
        {
            std::vector<std::shared_ptr<ResponseHandler>> handlers2;
            handlers2.emplace_back(std::make_shared<LambdaResponseHandler>(
                [](const std::string& input) { return false; },
                [](const ResponseMatch& match) {}
            ));
            std::string text2 = "text2";
            branch.AddPoint(text2, {}, handlers2);
            REQUIRE(branch.Length() == 2);
            REQUIRE(branch.GetPointAt(0)->GetText() == text1);
            REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == handlers1.size());
            REQUIRE(branch.GetPointAt(1)->GetText() == text2);
            REQUIRE(branch.GetPointAt(1)->GetHandlerCount() == handlers2.size());
        }
    }
    SECTION("add point by markup and handlers")
    {
        std::vector<std::function<std::string()>> expr;
        expr.emplace_back([]() { return "A"; });
        expr.emplace_back([]() { return "B"; });
        std::vector<std::shared_ptr<ResponseHandler>> handlers;
        handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
            [](const std::string& input) { return false; },
            [](const ResponseMatch& match) {}
        ));

        branch.AddPoint("text $0", expr, handlers);
        REQUIRE(branch.Length() == 1);
        REQUIRE(branch.GetPointAt(0)->GetText() == "text A");
        REQUIRE(branch.GetPointAt(0)->GetHandlerCount() == 1);
        branch.AddPoint("text $1", expr, handlers);
        REQUIRE(branch.Length() == 2);
        REQUIRE(branch.GetPointAt(1)->GetText() == "text B");
        REQUIRE(branch.GetPointAt(1)->GetHandlerCount() == 1);
    }
}

TEST_CASE("next point", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", {}, {});
    branch.AddPoint("2", {}, {});
    branch.AddPoint("3", {}, {});

    REQUIRE(branch.GetHead()->GetText() == "1");
    branch.Next();
    REQUIRE(branch.GetHead()->GetText() == "2");
    branch.Next();
    REQUIRE(branch.GetHead()->GetText() == "3");
    branch.Next();
    REQUIRE(branch.GetHead()->GetText() == "3");
}

TEST_CASE("previous point", "[StoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", {}, {});
    branch.AddPoint("2", {}, {});
    branch.AddPoint("3", {}, {});
    branch.Next();
    branch.Next();

    REQUIRE(branch.GetHead()->GetText() == "3");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetText() == "2");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetText() == "1");
    branch.Prev();
    REQUIRE(branch.GetHead()->GetText() == "1");

}

TEST_CASE("parent branch", "[StoryBranch]")
{
    StoryBranch parent;
    StoryBranch branch;
    REQUIRE(branch.GetParentBranch() == nullptr);
    branch.SetParentBranch(parent);
    REQUIRE(branch.GetParentBranch() != nullptr);
    branch.UnsetParentBranch();
    REQUIRE(branch.GetParentBranch() == nullptr);
}

TEST_CASE("branch name", "[StoryBranch]")
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
