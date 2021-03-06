/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "ResponseSystem.h"

namespace txt
{

TEST_CASE("ResponseSystem - LambdaResponseHandlers can be added", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("add LambdaResponseHandler by parameters")
    {
        sys.AddLambdaResponseHandler(
            [&key](const std::string& input) { return ResponseMatch(input == key); },
            [](const ResponseMatch& match) {}
        );
        REQUIRE(sys.HandlerCount() == 1);
    }
    SECTION("add LambdaResponseHandler by pointer")
    {
        LambdaResponseHandler handler(
            [&key](const std::string& input) { return ResponseMatch(input == key); },
            [](const ResponseMatch& match) {}
        );
        sys.AddHandler(std::make_shared<LambdaResponseHandler>(handler));
        REQUIRE(sys.HandlerCount() == 1);
    }
}

TEST_CASE("ResponseSystem - ResponseHandlers can be removed", "[ResponseSystem]")
{
    std::string key = "a";
    ResponseSystem sys;

    SECTION("remove from empty ResponseSystem")
    {
        sys.RemoveHandlers(key);
        REQUIRE(sys.HandlerCount() == 0);
    }
    SECTION("remove from non-empty ResponseSystem")
    {
        sys.AddLambdaResponseHandler(
            [&key](const std::string& input) { return input == key; },
            [](const ResponseMatch& match) {}
        );
        sys.AddLambdaResponseHandler(
            [&key](const std::string& input) { return input != key; },
            [](const ResponseMatch& match) {}
        );
        sys.RemoveHandlers(key);
        REQUIRE(sys.HandlerCount() == 1);
    }
}

TEST_CASE("ResponseSystem - Remove all ResponseHandlers", "[ResponseSystem]")
{
    ResponseSystem sys;

    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
    sys.AddLambdaResponseHandler(
        [](const std::string& input) { return input == "a"; },
        [](const ResponseMatch& match) {}
    );
    sys.AddLambdaResponseHandler(
        [](const std::string& input) { return input == "b"; },
        [](const ResponseMatch& match) {}
    );
    REQUIRE(sys.HandlerCount() == 2);
    sys.ClearHandlers();
    REQUIRE(sys.HandlerCount() == 0);
}

} // namespace txt
