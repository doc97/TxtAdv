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
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "_hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("_hello_ _world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello _world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::ITALIC);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("_hello world_");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::ITALIC);
    }
    SECTION("test 4")
    {
        Text txt("__normal");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("___italic_");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "italic");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::ITALIC);
    }
}

TEST_CASE("Text - bold", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("*hello world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "*hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("*hello* *world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello *world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("*hello world*");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
    SECTION("test 4")
    {
        Text txt("**normal");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("***bold*");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "bold");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 4);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
}

TEST_CASE("Text - strikethrough", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("~hello world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "~hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 2")
    {
        Text txt("~hello~ ~world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello ~world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 7);
        REQUIRE(styles[1].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("~hello world~");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
    SECTION("test 4")
    {
        Text txt("~~normal");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("~~~strikethrough~");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
}

TEST_CASE("Text - underline", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("__hello world__");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::UNDERL);
    }
    SECTION("test 2")
    {
        Text txt("__hello__ __world");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::UNDERL);
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 6);
        REQUIRE(styles[1].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 3")
    {
        Text txt("~hello world~");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
    SECTION("test 4")
    {
        Text txt("~~normal");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NORMAL);
    }
    SECTION("test 5")
    {
        Text txt("~~~strikethrough~");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
}

TEST_CASE("Text - style combination", "[Text]")
{
    SECTION("bold + italics")
    {
        Text txt("*_hello world_*");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::BOLD | Emphasis::ITALIC));
    }
    SECTION("underline + italics")
    {
        Text txt("___hello world___");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::ITALIC));
    }
    SECTION("underline + bold + strike")
    {
        Text txt("__*~hello world~*__");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::BOLD | Emphasis::STRIKE));
    }
    SECTION("mix")
    {
        Text txt("__*hello__ ~world~*");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 3);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::BOLD));
        REQUIRE(styles[1].start == 5);
        REQUIRE(styles[1].len == 1);
        REQUIRE(styles[1].bitmask == Emphasis::BOLD);
        REQUIRE(styles[2].start == 6);
        REQUIRE(styles[2].len == 5);
        REQUIRE(styles[2].bitmask == (Emphasis::BOLD | Emphasis::STRIKE));
    }
}

TEST_CASE("Text - size metadata", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("!2hello");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].size == TextSize::S2);
    }
    SECTION("test 2")
    {
        Text txt("!2hello world");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 11);
        REQUIRE(metadata[0].size == TextSize::S2);
    }
    SECTION("test 3")
    {
        Text txt("!3hello");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].size == TextSize::S3);
    }
}

TEST_CASE("Text - color metadata", "[Text]")
{
    SECTION("single color")
    {
        Color color = { 0x33, 0xFF, 0xEE, 0xFF };
        Text txt("#33FFEEFFhello");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(txt.Str() == "hello");
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].color == color);
    }
    SECTION("multi-color")
    {
        Color color0 = { 0xFF, 0xFF, 0xFF, 0xFF };
        Color color1 = { 0x11, 0x22, 0x33, 0x44 };
        Color color2 = { 0x55, 0x66, 0x77, 0x88 };
        Text txt("he#11223344llo#55667788 world");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(metadata.size() == 3);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 2);
        REQUIRE(metadata[0].color == color0);
        REQUIRE(metadata[1].start == 2);
        REQUIRE(metadata[1].len == 3);
        REQUIRE(metadata[1].color == color1);
        REQUIRE(metadata[2].start == 5);
        REQUIRE(metadata[2].len == 6);
        REQUIRE(metadata[2].color == color2);
    }
}

TEST_CASE("Text - metadata compression", "[Text]")
{
    Text txt("hel!1lo");
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
}

} // namespace txt
