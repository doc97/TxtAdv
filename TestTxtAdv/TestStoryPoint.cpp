#include "catch.hpp"
#include "StoryPoint.h"

TEST_CASE("get/set text", "[StoryPoint]")
{
    StoryPoint point;
    point.SetText("a");
    REQUIRE(point.GetText() == "a");
    point.SetText("b");
    REQUIRE(point.GetText() == "b");
}