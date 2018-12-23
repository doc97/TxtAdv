/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "LuaStoryBranch.h"

namespace txt
{

TEST_CASE("LuaStoryBranch - configuration", "[LuaStoryBranch]")
{
    REQUIRE(LuaStoryBranch::className == "LuaStoryBranch");
}

TEST_CASE("LuaStoryBranch - registered methods", "[LuaStoryBranch]")
{
    bool hasNext = false;
    bool hasPrev = false;
    for (size_t i = 0; LuaStoryBranch::methods[i].name; ++i)
    {
        if (LuaStoryBranch::methods[i].name == "next")
            hasNext = true;
        if (LuaStoryBranch::methods[i].name == "prev")
            hasPrev = true;
    }
    REQUIRE(hasNext);
    REQUIRE(hasPrev);
}

TEST_CASE("LuaStoryBranch - next/prev", "[LuaStoryBranch]")
{
    StoryBranch branch;
    branch.AddPoint("1", {}, {});
    branch.AddPoint("2", {}, {});
    branch.AddPoint("3", {}, {});
    LuaStoryBranch wrapper(&branch);
    REQUIRE(branch.GetHead()->GetText() == "1");

    SECTION("next")
    {
        wrapper.Next();
        REQUIRE(branch.GetHead()->GetText() == "2");
        wrapper.Next();
        REQUIRE(branch.GetHead()->GetText() == "3");
        wrapper.Next();
        REQUIRE(branch.GetHead()->GetText() == "3");
    }
    SECTION("prev")
    {
        wrapper.Prev();
        REQUIRE(branch.GetHead()->GetText() == "1");
        branch.SetCurrentPoint(2);
        wrapper.Prev();
        REQUIRE(branch.GetHead()->GetText() == "2");
        wrapper.Prev();
        REQUIRE(branch.GetHead()->GetText() == "1");
    }
}

} // namespace txt
