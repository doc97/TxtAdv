/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "Text.h"

namespace txt
{

TEST_CASE("Text - no markup", "[Text]")
{
    SECTION("test 1")
    {
        std::string raw = "hello world";
        Text txt(raw);
        REQUIRE(txt.Str() == raw);
    }
    SECTION("test 2")
    {
        std::string raw = "foobar";
        Text txt(raw);
        REQUIRE(txt.Str() == raw);
    }
}

TEST_CASE("Text - italics", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("_hello world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "_hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("_hello_ _world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello _world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].style == Styles::ITALIC);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].style == Styles::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("_hello world_");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == Styles::ITALIC);
    }
    SECTION("test 4")
    {
        Text txt("__normal");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("___italic_");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "italic");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].style == Styles::ITALIC);
    }
}

} // namespace txt
