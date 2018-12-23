/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "LambdaResponseHandler.h"
#include <string>

namespace txt
{

typedef std::function<ResponseMatch(const std::string&)> MatchFunc;

TEST_CASE("LambdaResponseHandler - matcher function", "[LambdaResponseHandler]")
{
    LambdaResponseHandler trueHandler([](const std::string& input) { return ResponseMatch(true); },
        [](const ResponseMatch& match) {});
    LambdaResponseHandler falseHandler([](const std::string& input) { return ResponseMatch(false); },
        [](const ResponseMatch& match) {});
    REQUIRE(trueHandler.Matches(""));
    REQUIRE(!falseHandler.Matches(""));
}

TEST_CASE("LambdaResponseHandler - action function", "[LambdaResponseHandler]")
{
    std::string key = "key";
    bool isHandled = false;
    MatchFunc matcher = [&key](const std::string& input) { return input == key; };
    std::function<void(const ResponseMatch&)> action = [&isHandled](const ResponseMatch& match) { isHandled = true; };
    LambdaResponseHandler handler(matcher, action);

    SECTION("matching key")
    {
        handler.HandleInput(key);
        REQUIRE(isHandled);

    }
    SECTION("non-matching key")
    {
        handler.HandleInput("b");
        REQUIRE(!isHandled);
    }
}

} // namespace txt
