/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "Text.h"

namespace txt
{

TEST_CASE("Text - raw", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("_italics_");
        REQUIRE(txt.RawStr() == "_italics_");
    }
    SECTION("test 2")
    {
        Text txt("*bold*");
        REQUIRE(txt.RawStr() == "*bold*");
    }
    SECTION("test 3")
    {
        Text txt("~strike~");
        REQUIRE(txt.RawStr() == "~strike~");
    }
    SECTION("test 4")
    {
        Text txt("__under__");
        REQUIRE(txt.RawStr() == "__under__");
    }
}

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

TEST_CASE("Text - bold", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("*hello world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "*hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("*hello* *world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello *world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].style == Styles::BOLD);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].style == Styles::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("*hello world*");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == Styles::BOLD);
    }
    SECTION("test 4")
    {
        Text txt("**normal");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("***bold*");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "bold");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 4);
        REQUIRE(styles[0].style == Styles::BOLD);
    }
}

TEST_CASE("Text - strikethrough", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("~hello world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "~hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("~hello~ ~world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello ~world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].style == Styles::STRIKE);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].style == Styles::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("~hello world~");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == Styles::STRIKE);
    }
    SECTION("test 4")
    {
        Text txt("~~normal");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("~~~strikethrough~");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].style == Styles::STRIKE);
    }
}

TEST_CASE("Text - underline", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("__hello world__");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == Styles::UNDERL);
    }
    SECTION("test 2")
    {
        Text txt("__hello__ __world");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].style == Styles::UNDERL);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 6);
        REQUIRE(styles[1].style == Styles::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("~hello world~");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == Styles::STRIKE);
    }
    SECTION("test 4")
    {
        Text txt("~~normal");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].style == Styles::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("~~~strikethrough~");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].style == Styles::STRIKE);
    }
}

TEST_CASE("Text - combination", "[Text]")
{
    SECTION("bold + italics")
    {
        Text txt("*_hello world_*");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == (Styles::BOLD | Styles::ITALIC));
    }
    SECTION("underline + italics")
    {
        Text txt("___hello world___");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == (Styles::UNDERL | Styles::ITALIC));
    }
    SECTION("underline + bold + strike")
    {
        Text txt("__*~hello world~*__");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].style == (Styles::UNDERL | Styles::BOLD | Styles::STRIKE));
    }
    SECTION("mix")
    {
        Text txt("__*hello__ ~world~*");
        std::vector<TextStyle> styles = txt.GetStyles();
        REQUIRE(styles.size() == 3);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].style == (Styles::UNDERL | Styles::BOLD));
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 1);
        REQUIRE(styles[1].style == Styles::BOLD);
        REQUIRE(styles[2].start == 6);
        REQUIRE(styles[2].len == 5);
        REQUIRE(styles[2].style == (Styles::BOLD | Styles::STRIKE));
    }
}

} // namespace txt
