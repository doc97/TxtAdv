/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "TextStyleSheet.h"
#include "TextMarkup.h"

namespace txt
{

TEST_CASE("TextStyleSheet - get non-existing style", "[TextStyleSheet]")
{
    TextStyleSheet tss;
    TextStyle defStyle;
    TextStyle style = tss.GetStyle("test");
    REQUIRE(style == defStyle);
}

TEST_CASE("TextStyleSheet - get existing style", "[TextStyleSheet]")
{
    TextStyleSheet tss;

    SECTION("test 1")
    {
        TextStyle customStyle;
        customStyle.size = TextSize::S2;
        customStyle.bitmask = Emphasis::STRIKE;
        tss.SetStyle("test", customStyle);
        REQUIRE(tss.GetStyle("test") == customStyle);
    }

    SECTION("get existing style 2")
    {
        TextStyle customStyle1;
        customStyle1.size = TextSize::S2;
        TextStyle customStyle2;
        customStyle2.size = TextSize::S3;
        tss.SetStyle("test1", customStyle1);
        tss.SetStyle("test2", customStyle2);
        REQUIRE(tss.GetStyle("test1") == customStyle1);
        REQUIRE(tss.GetStyle("test2") == customStyle2);
    }
}

TEST_CASE("TextStyleSheet - overwrite style", "[TextStyleSheet]")
{
    TextStyle style;
    style.size = TextSize::S2;
    style.bitmask = Emphasis::ITALIC;
    TextStyleSheet tss;
    tss.SetStyle("test", style);

    TextStyle custom;
    custom.size = TextSize::S3;
    custom.bitmask = Emphasis::UNDERL;
    tss.SetStyle("test", custom);
    REQUIRE(tss.GetStyle("test") == custom);
}

TEST_CASE("TextStyleSheet - remove style", "[TextStyleSheet]")
{
    TextStyle defStyle;
    TextStyle style;
    style.size = TextSize::S4;
    style.bitmask = (Emphasis::BOLD | Emphasis::ITALIC);
    TextStyleSheet tss;

    SECTION("remove non-existing style")
    {
        tss.UnsetStyle("test");
        REQUIRE(tss.GetStyle("test") == defStyle);
    }
    SECTION("remove existing style")
    {
        tss.SetStyle("test", style);
        tss.UnsetStyle("test");
        REQUIRE(tss.GetStyle("test") == defStyle);
    }
}

TEST_CASE("TextStyleSheet - has style", "[TextStyleSheet]")
{
    TextStyle style;
    style.size = TextSize::S4;
    style.bitmask = Emphasis::BOLD;
    TextStyleSheet tss;
    REQUIRE(!tss.HasStyle("test"));
    tss.SetStyle("test", style);
    REQUIRE(tss.HasStyle("test"));
}

TEST_CASE("TextStyleSheet - apply default style sheet", "[TextStyleSheet]")
{
    TextMarkup markup("<a>hello</a>");
    Text txt = markup.GetText();
    TextStyleSheet tss;
    tss.Apply(txt);
    std::vector<TextEmphasis> emphasis = txt.GetEmphasisStyles();
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(emphasis.size() == 1);
    REQUIRE(metadata.size() == 1);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
    REQUIRE(metadata[0].size == TextSize::S1);
}

TEST_CASE("TextStyleSheet - apply style sheet to text without matching tags", "[TextStyleSheet]")
{
    TextStyle style;
    style.size = TextSize::S2;
    TextStyleSheet tss;
    tss.SetStyle("b", style);
    TextMarkup markup("<a>hello</a>");
    Text txt = markup.GetText();
    tss.Apply(txt);
    std::vector<TextEmphasis> emphasis = txt.GetEmphasisStyles();
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(emphasis.size() == 1);
    REQUIRE(metadata.size() == 1);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
    REQUIRE(metadata[0].size == TextSize::S1);
}

TEST_CASE("TextStyleSheet - apply style sheet to text with matching tag", "[TextStyleSheet]")
{
    TextStyle style;
    style.size = TextSize::S2;
    TextStyleSheet tss;
    tss.SetStyle("a", style);
    TextMarkup markup("<a>hello</a>");
    Text txt = markup.GetText();
    tss.Apply(txt);
    std::vector<TextEmphasis> emphasis = txt.GetEmphasisStyles();
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(emphasis.size() == 1);
    REQUIRE(metadata.size() == 1);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
    REQUIRE(metadata[0].size == TextSize::S2);
}

TEST_CASE("TextStyleSheet - apply style sheet to text with mixed styles", "[TextStyleSheet]")
{
    TextStyle style;
    style.size = TextSize::S2;
    style.bitmask = Emphasis::BOLD;
    TextStyleSheet tss;
    tss.SetStyle("a", style);
    TextMarkup markup("hel_lo <a>wo_rld</a>");
    Text txt = markup.GetText();
    tss.Apply(txt);
    std::vector<TextEmphasis> emphasis = txt.GetEmphasisStyles();
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(emphasis.size() == 3);
    REQUIRE(metadata.size() == 2);
    REQUIRE(emphasis[0].start == 0);
    REQUIRE(emphasis[0].len == 3);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
    REQUIRE(emphasis[1].start == 3);
    REQUIRE(emphasis[1].len == 3);
    REQUIRE(emphasis[1].bitmask == Emphasis::ITALIC);
    REQUIRE(emphasis[2].start == 6);
    REQUIRE(emphasis[2].len == 5);
    REQUIRE(emphasis[2].bitmask == Emphasis::BOLD);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 6);
    REQUIRE(metadata[0].size == TextSize::S1);
    REQUIRE(metadata[1].start == 6);
    REQUIRE(metadata[1].len == 5);
    REQUIRE(metadata[1].size == TextSize::S2);
}

} // namespace txt
