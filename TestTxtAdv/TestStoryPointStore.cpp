/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StoryPointStore.h"

namespace txt
{

TEST_CASE("StoryPointStore - add/get story point", "[StoryPointStore]")
{
    StoryPointStore store;

    SECTION("no existing point")
    {
        try
        {
            StoryPoint result = store.Get("0");
            FAIL("Trying to access a non-existent point should throw std::out_of_range");
        }
        catch (std::out_of_range) {}
    }
    SECTION("one point")
    {
        StoryPoint point("0");
        point.SetTextStr("text");
        store.Add(point);
        REQUIRE(store.Get("0").GetTextStr() == "text");
    }
}

} // namespace txt
