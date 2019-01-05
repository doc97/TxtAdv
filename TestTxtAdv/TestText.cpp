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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[1].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[1].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[1].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[1].bitmask == Emphasis::NONE);
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
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
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
    SECTION("underline + bold + italics")
    {
        Text txt("__*_hello world_*__");
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::BOLD | Emphasis::ITALIC));
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

TEST_CASE("Text - no tags", "[Text]")
{
    Text txt("hello");
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 0);
    REQUIRE(txt.Str() == "hello");
    REQUIRE(txt.RawStr() == "hello");
}

TEST_CASE("Text - one invalid tag", "[Text]")
{
    SECTION("unclosed tag")
    {
        Text txt("<open>hello");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<open>hello");
        REQUIRE(txt.RawStr() == "<open>hello");
    }
    SECTION("non-matching tag 1")
    {
        Text txt("<open>hello</opened>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<open>hello</opened>");
        REQUIRE(txt.RawStr() == "<open>hello</opened>");
    }
}

TEST_CASE("Text - one valid tag", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("<test>hello</test>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 5);
        REQUIRE(tags[0].name == "test");
        REQUIRE(txt.Str() == "hello");
        REQUIRE(txt.RawStr() == "<test>hello</test>");
    }
    SECTION("test 2")
    {
        Text txt("hello <best>world!</best>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 6);
        REQUIRE(tags[0].len == 6);
        REQUIRE(tags[0].name == "best");
        REQUIRE(txt.Str() == "hello world!");
        REQUIRE(txt.RawStr() == "hello <best>world!</best>");
    }
    SECTION("test 3")
    {
        Text txt("hello <testing>world!</testing>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 6);
        REQUIRE(tags[0].len == 6);
        REQUIRE(tags[0].name == "testing");
        REQUIRE(txt.Str() == "hello world!");
        REQUIRE(txt.RawStr() == "hello <testing>world!</testing>");
    }
}

TEST_CASE("Text - nested tags not allowed", "[Text]")
{
    Text txt("<a>hello <b>world</b></a>");
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 1);
    REQUIRE(tags[0].start == 0);
    REQUIRE(tags[0].len == 18);
    REQUIRE(tags[0].name == "a");
    REQUIRE(txt.Str() == "hello <b>world</b>");
}

TEST_CASE("Text - multiple same tags", "[Text]")
{
    Text txt("<a>hello</a> <a>world</a>");
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 2);
    REQUIRE(tags[0].start == 0);
    REQUIRE(tags[0].len == 5);
    REQUIRE(tags[0].name == "a");
    REQUIRE(tags[1].start == 6);
    REQUIRE(tags[1].len == 5);
    REQUIRE(tags[1].name == "a");
    REQUIRE(txt.Str() == "hello world");
}

TEST_CASE("Text - multiple different tags", "[Text]")
{
    Text txt("<a>hello</a> <b>world</b> <c>to you</c>!");
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0].start == 0);
    REQUIRE(tags[0].len == 5);
    REQUIRE(tags[0].name == "a");
    REQUIRE(tags[1].start == 6);
    REQUIRE(tags[1].len == 5);
    REQUIRE(tags[1].name == "b");
    REQUIRE(tags[2].start == 12);
    REQUIRE(tags[2].len == 6);
    REQUIRE(tags[2].name == "c");
    REQUIRE(txt.Str() == "hello world to you!");
}

TEST_CASE("Text - tag + bold markup", "[Text")
{
    SECTION("tag out, bold in")
    {
        Text txt("<a>*hello*</a>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 5);
        REQUIRE(tags[0].name == "a");
        REQUIRE(txt.Str() == "hello");
        REQUIRE(txt.RawStr() == "<a>*hello*</a>");

        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
    SECTION("tag in, bold out")
    {
        Text txt("*<a>hello</a>*");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 5);
        REQUIRE(tags[0].name == "a");
        REQUIRE(txt.Str() == "hello");
        REQUIRE(txt.RawStr() == "*<a>hello</a>*");

        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
    SECTION("tag and bold mix 1")
    {
        Text txt("*<a>hello*</a>");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 5);
        REQUIRE(tags[0].name == "a");
        REQUIRE(txt.Str() == "hello");
        REQUIRE(txt.RawStr() == "*<a>hello*</a>");

        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
    SECTION("tag and bold mix 2")
    {
        Text txt("*<a>h*e*llo</a>*");
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 5);
        REQUIRE(tags[0].name == "a");
        REQUIRE(txt.Str() == "hello");
        REQUIRE(txt.RawStr() == "*<a>h*e*llo</a>*");

        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 3);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 1);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
        REQUIRE(styles[1].start == 1);
        REQUIRE(styles[1].len == 1);
        REQUIRE(styles[1].bitmask == Emphasis::NONE);
        REQUIRE(styles[2].start == 2);
        REQUIRE(styles[2].len == 3);
        REQUIRE(styles[2].bitmask == Emphasis::BOLD);
    }
}

TEST_CASE("Text - escape emphasis", "[Text]")
{
    Text txt("he\\*llo*");
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(txt.RawStr() == "he\\*llo*");
    REQUIRE(txt.Str() == "he*llo*");
}

TEST_CASE("Text - escape metadata", "[Text]")
{
    SECTION("color metadata")
    {
        Text txt("he\\#11223344llo");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(txt.RawStr() == "he\\#11223344llo");
        REQUIRE(txt.Str() == "he#11223344llo");
    }
    SECTION("size metadata")
    {
        Text txt("he\\!2llo");
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(txt.RawStr() == "he\\!2llo");
        REQUIRE(txt.Str() == "he!2llo");
    }
}

TEST_CASE("Text - Escape escape", "[Text]")
{
    SECTION("test 1")
    {
        Text txt("\\hello");
        REQUIRE(txt.RawStr() == "\\hello");
        REQUIRE(txt.Str() == "hello");
    }
    SECTION("test 2")
    {
        Text txt("\\\\hello");
        REQUIRE(txt.RawStr() == "\\\\hello");
        REQUIRE(txt.Str() == "\\hello");
    }
    SECTION("test 3")
    {
        Text txt("\\\\\\hello");
        REQUIRE(txt.RawStr() == "\\\\\\hello");
        REQUIRE(txt.Str() == "\\hello");
    }
}

} // namespace txt
