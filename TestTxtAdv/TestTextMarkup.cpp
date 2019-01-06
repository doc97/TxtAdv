/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "TextMarkup.h"

namespace txt
{

TEST_CASE("TextMarkup - no markup", "[TextMarkup]")
{
    SECTION("test 1")
    {
        std::string raw = "hello world";
        TextMarkup markup(raw);
        REQUIRE(markup.GetText().RawStr() == raw);
    }
    SECTION("test 2")
    {
        std::string raw = "foobar";
        TextMarkup markup(raw);
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(txt.Str() == raw);
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 6);
        REQUIRE(metadata[0].size == TextSize::S1);
        REQUIRE(metadata[0].outline_color == Color{ 255, 255, 255, 255 });
        REQUIRE(metadata[0].fill_color == Color{ 255, 255, 255, 255 });
        REQUIRE(metadata[0].bg_color == Color{ 0, 0, 0, 0 });
        REQUIRE(tags.size() == 0);
    }
    SECTION("test 3")
    {
        TextMarkup markup("hello");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 5);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].size == TextSize::S1);
        REQUIRE(metadata[0].outline_color == Color{ 255, 255, 255, 255 });
        REQUIRE(metadata[0].fill_color == Color{ 255, 255, 255, 255 });
        REQUIRE(metadata[0].bg_color == Color{ 0, 0, 0, 0 });
        REQUIRE(tags.size() == 0);
    }
}

TEST_CASE("TextMarkup - raw str", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("_italics_");
        REQUIRE(markup.GetText().RawStr() == "_italics_");
    }
    SECTION("test 2")
    {
        TextMarkup markup("*bold*");
        REQUIRE(markup.GetText().RawStr() == "*bold*");
    }
    SECTION("test 3")
    {
        TextMarkup markup("~strike~");
        REQUIRE(markup.GetText().RawStr() == "~strike~");
    }
    SECTION("test 4")
    {
        TextMarkup markup("__under__");
        REQUIRE(markup.GetText().RawStr() == "__under__");
    }
}

TEST_CASE("TextMarkup - italics", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("_hello world");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "_hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 2")
    {
        TextMarkup markup("_hello_ _world");
        Text txt = markup.GetText();
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
        TextMarkup markup("_hello world_");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::ITALIC);
    }
    SECTION("test 4")
    {
        TextMarkup markup("__normal");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 5")
    {
        TextMarkup markup("___italic_");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "italic");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::ITALIC);
    }
}

TEST_CASE("TextMarkup - bold", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("*hello world");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "*hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 2")
    {
        TextMarkup markup("*hello* *world");
        Text txt = markup.GetText();
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
        TextMarkup markup("*hello world*");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
    SECTION("test 4")
    {
        TextMarkup markup("**normal");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 5")
    {
        TextMarkup markup("***bold*");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "bold");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 4);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    }
}

TEST_CASE("TextMarkup - strikethrough", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("~hello world");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "~hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 12);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 2")
    {
        TextMarkup markup("~hello~ ~world");
        Text txt = markup.GetText();
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
        TextMarkup markup("~hello world~");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
    SECTION("test 4")
    {
        TextMarkup markup("normal");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 5")
    {
        TextMarkup markup("~strikethrough~");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
}

TEST_CASE("TextMarkup - underline", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("__hello world__");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::UNDERL);
    }
    SECTION("test 2")
    {
        TextMarkup markup("__hello__ __world");
        Text txt = markup.GetText();
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
        TextMarkup markup("~hello world~");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
    SECTION("test 4")
    {
        TextMarkup markup("~~normal");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "normal");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
    }
    SECTION("test 5")
    {
        TextMarkup markup("~~~strikethrough~");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(txt.Str() == "strikethrough");
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 13);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
    }
}

TEST_CASE("TextMarkup markup style combination", "[TextMarkup]")
{
    SECTION("bold + italics")
    {
        TextMarkup markup("*_hello world_*");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::BOLD | Emphasis::ITALIC));
    }
    SECTION("underline + italics")
    {
        TextMarkup markup("___hello world___");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::ITALIC));
    }
    SECTION("underline + bold + italics")
    {
        TextMarkup markup("__*_hello world_*__");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::BOLD | Emphasis::ITALIC));
    }
    SECTION("underline + bold + strike")
    {
        TextMarkup markup("__*~hello world~*__");
        Text txt = markup.GetText();
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 1);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 11);
        REQUIRE(styles[0].bitmask == (Emphasis::UNDERL | Emphasis::BOLD | Emphasis::STRIKE));
    }
    SECTION("mix")
    {
        TextMarkup markup("__*hello__ ~world~*");
        Text txt = markup.GetText();
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

TEST_CASE("TextMarkup - emphasis all", "[TextMarkup]")
{
    TextMarkup markup("_*__~hello~__*_");
    Text txt = markup.GetText();
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 5);
    REQUIRE(styles[0].bitmask == (Emphasis::ITALIC | Emphasis::BOLD | Emphasis::UNDERL | Emphasis::STRIKE));
    REQUIRE(styles[0].bitmask == Emphasis::ALL);
}

TEST_CASE("TextMarkup - emphasis mixed", "[TextMarkup]")
{
    TextMarkup markup("_*__~hello___*~");
    Text txt = markup.GetText();
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 5);
    REQUIRE(styles[0].bitmask == (Emphasis::ITALIC | Emphasis::BOLD | Emphasis::UNDERL | Emphasis::STRIKE));
}

TEST_CASE("TextMarkup - size metadata", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("!2hello");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].size == TextSize::S2);
    }
    SECTION("test 2")
    {
        TextMarkup markup("!2hello world");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 11);
        REQUIRE(metadata[0].size == TextSize::S2);
    }
    SECTION("test 3")
    {
        TextMarkup markup("!3hello");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].size == TextSize::S3);
    }
}

TEST_CASE("TextMarkup - color metadata", "[TextMarkup]")
{
    SECTION("single color")
    {
        Color color = { 0x33, 0xFF, 0xEE, 0xFF };
        TextMarkup markup("#33FFEEFFhello");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(txt.Str() == "hello");
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 5);
        REQUIRE(metadata[0].fill_color == color);
    }
    SECTION("multi-color")
    {
        Color color0 = { 0xFF, 0xFF, 0xFF, 0xFF };
        Color color1 = { 0x11, 0x22, 0x33, 0x44 };
        Color color2 = { 0x55, 0x66, 0x77, 0x88 };
        TextMarkup markup("he#11223344llo#55667788 world");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(txt.Str() == "hello world");
        REQUIRE(metadata.size() == 3);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 2);
        REQUIRE(metadata[0].fill_color == color0);
        REQUIRE(metadata[1].start == 2);
        REQUIRE(metadata[1].len == 3);
        REQUIRE(metadata[1].fill_color == color1);
        REQUIRE(metadata[2].start == 5);
        REQUIRE(metadata[2].len == 6);
        REQUIRE(metadata[2].fill_color == color2);
    }
}

TEST_CASE("TextMarkup - no tags", "[TextMarkup]")
{
    TextMarkup markup("hello");
    Text txt = markup.GetText();
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 0);
    REQUIRE(txt.Str() == "hello");
    REQUIRE(txt.RawStr() == "hello");
}

TEST_CASE("TextMarkup - one invalid tag", "[TextMarkup]")
{
    SECTION("unclosed tag")
    {
        TextMarkup markup("<open>hello");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<open>hello");
        REQUIRE(txt.RawStr() == "<open>hello");
    }
    SECTION("non-matching tag 1")
    {
        TextMarkup markup("<open>hello</opened>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<open>hello</opened>");
        REQUIRE(txt.RawStr() == "<open>hello</opened>");
    }
}

TEST_CASE("TextMarkup - one valid tag", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("<test>hello</test>");
        Text txt = markup.GetText();
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
        TextMarkup markup("hello <best>world!</best>");
        Text txt = markup.GetText();
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
        TextMarkup markup("hello <testing>world!</testing>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 6);
        REQUIRE(tags[0].len == 6);
        REQUIRE(tags[0].name == "testing");
        REQUIRE(txt.Str() == "hello world!");
        REQUIRE(txt.RawStr() == "hello <testing>world!</testing>");
    }
}

TEST_CASE("TextMarkup - nested tags not allowed", "[TextMarkup]")
{
    TextMarkup markup("<a>hello <b>world</b></a>");
    Text txt = markup.GetText();
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 1);
    REQUIRE(tags[0].start == 0);
    REQUIRE(tags[0].len == 18);
    REQUIRE(tags[0].name == "a");
    REQUIRE(txt.Str() == "hello <b>world</b>");
}

TEST_CASE("TextMarkup - multiple same tags", "[TextMarkup]")
{
    TextMarkup markup("<a>hello</a> <a>world</a>");
    Text txt = markup.GetText();
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

TEST_CASE("TextMarkup - multiple different tags", "[TextMarkup]")
{
    TextMarkup markup("<a>hello</a> <b>world</b> <c>to you</c>!");
    Text txt = markup.GetText();
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

TEST_CASE("TextMarkup - tag + bold markup", "[TextMarkup]")
{
    SECTION("tag out, bold in")
    {
        TextMarkup markup("<a>*hello*</a>");
        Text txt = markup.GetText();
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
        TextMarkup markup("*<a>hello</a>*");
        Text txt = markup.GetText();
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
        TextMarkup markup("*<a>hello*</a>");
        Text txt = markup.GetText();
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
        TextMarkup markup("*<a>h*e*llo</a>*");
        Text txt = markup.GetText();
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

TEST_CASE("TextMarkup - escape emphasis", "[TextMarkup]")
{
    TextMarkup markup("he\\*llo*");
    Text txt = markup.GetText();
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(txt.RawStr() == "he\\*llo*");
    REQUIRE(txt.Str() == "he*llo*");
}

TEST_CASE("TextMarkup - escape metadata", "[TextMarkup]")
{
    SECTION("color metadata")
    {
        TextMarkup markup("he\\#11223344llo");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(txt.RawStr() == "he\\#11223344llo");
        REQUIRE(txt.Str() == "he#11223344llo");
    }
    SECTION("size metadata")
    {
        TextMarkup markup("he\\!2llo");
        Text txt = markup.GetText();
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(txt.RawStr() == "he\\!2llo");
        REQUIRE(txt.Str() == "he!2llo");
    }
}

TEST_CASE("TextMarkup - escape start tag", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("\\<a>hello</a>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<a>hello</a>");
    }
    SECTION("test 2")
    {
        TextMarkup markup("<a\\>hello</a>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<a>hello</a>");
    }
}

TEST_CASE("TextMarkup - escape end tag", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("<a>hello\\</a>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<a>hello</a>");
    }
    SECTION("test 2")
    {
        TextMarkup markup("<a>hello<\\/a>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<a>hello</a>");
    }
    SECTION("test 3")
    {
        TextMarkup markup("<a>hello</a\\>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 0);
        REQUIRE(txt.Str() == "<a>hello</a>");
    }
}

TEST_CASE("TextMarkup - escape and saved tag", "[TextMarkup]")
{
    TextMarkup markup("<a>hello\\</a></a>");
    Text txt = markup.GetText();
    std::vector<TextTag> tags = txt.GetTags();
    REQUIRE(tags.size() == 1);
    REQUIRE(txt.Str() == "hello</a>");
}

TEST_CASE("TextMarkup - Escape escape", "[TextMarkup]")
{
    SECTION("test 1")
    {
        TextMarkup markup("\\hello");
        Text txt = markup.GetText();
        REQUIRE(txt.RawStr() == "\\hello");
        REQUIRE(txt.Str() == "hello");
    }
    SECTION("test 2")
    {
        TextMarkup markup("\\\\hello");
        Text txt = markup.GetText();
        REQUIRE(txt.RawStr() == "\\\\hello");
        REQUIRE(txt.Str() == "\\hello");
    }
    SECTION("test 3")
    {
        TextMarkup markup("\\\\\\hello");
        Text txt = markup.GetText();
        REQUIRE(txt.RawStr() == "\\\\\\hello");
        REQUIRE(txt.Str() == "\\hello");
    }
}

TEST_CASE("TextMarkup - emphasis compression", "[TextMarkup]")
{
    TextMarkup markup("he**ll**o");
    Text txt = markup.GetText();
    std::vector<TextEmphasis> emphasis = txt.GetEmphasisStyles();
    REQUIRE(emphasis.size() == 1);
    REQUIRE(emphasis[0].start == 0);
    REQUIRE(emphasis[0].len == 5);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
}

TEST_CASE("TextMarkup - metadata compression", "[TextMarkup]")
{
    TextMetadata expected;
    TextMarkup markup("hel!1lo");
    Text txt = markup.GetText();
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 5);
    REQUIRE(metadata[0] == expected);
}

TEST_CASE("TextMarkup - tag compression", "[TextMarkup]")
{
    SECTION("compressed")
    {
        TextMarkup markup("<a>foo</a><a>bar</a>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 1);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 6);
        REQUIRE(tags[0].name == "a");
    }
    SECTION("not compressed")
    {
        TextMarkup markup("<a>foo</a><b>bar</b>");
        Text txt = markup.GetText();
        std::vector<TextTag> tags = txt.GetTags();
        REQUIRE(tags.size() == 2);
        REQUIRE(tags[0].start == 0);
        REQUIRE(tags[0].len == 3);
        REQUIRE(tags[0].name == "a");
        REQUIRE(tags[1].start == 3);
        REQUIRE(tags[1].len == 3);
        REQUIRE(tags[1].name == "b");
    }
}

} // namespace txt
