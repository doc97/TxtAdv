#include "catch.hpp"
#include "ResponseMatch.h"

namespace txt
{

TEST_CASE("isMatch", "[ResponseMatch]")
{
    SECTION("boolean constructor")
    {
        ResponseMatch match(true);
        REQUIRE(match.IsMatch());
        match = ResponseMatch(false);
        REQUIRE(!match.IsMatch());
    }
    SECTION("boolean & capture constructor")
    {
        ResponseMatch match(true, {});
        REQUIRE(match.IsMatch());
        match = ResponseMatch(false, {});
        REQUIRE(!match.IsMatch());
    }
}

TEST_CASE("captures", "[ResponseMatch]")
{
    ResponseMatch match(true, {});
    REQUIRE(match.CaptureCount() == 0);
    match = ResponseMatch(true, { "a" });
    REQUIRE(match.CaptureCount() == 1);
    REQUIRE(match.GetCapture(0) == "a");
    match = ResponseMatch(true, { "b", "c" });
    REQUIRE(match.CaptureCount() == 2);
    REQUIRE(match.GetCapture(0) == "b");
    REQUIRE(match.GetCapture(1) == "c");

    try
    {
        match.GetCapture(2);
        FAIL("Accessing with out-of-range index should throw std::out_of_range");
    }
    catch (std::out_of_range) {}
}

} // namespace txt
