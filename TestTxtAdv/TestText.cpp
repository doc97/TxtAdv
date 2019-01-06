/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "Text.h"
#include "TextMarkup.h"

namespace txt
{

TEST_CASE("Text - set new emphasis style", "[Text]")
{
    TextMarkup markup("hello world");
    Text txt = markup.GetText();
    txt.SetEmphasisStyle(0, 11, Emphasis::BOLD);
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 11);
    REQUIRE(styles[0].bitmask == Emphasis::BOLD);
}

TEST_CASE("Text - change emphasis style", "[Text]")
{
    SECTION("test 1")
    {
        TextMarkup markup("*hello* _world_");
        Text txt = markup.GetText();
        txt.SetEmphasisStyle(3, 6, Emphasis::UNDERL);
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 3);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 3);
        REQUIRE(styles[0].bitmask == Emphasis::BOLD);
        REQUIRE(styles[1].start == 3);
        REQUIRE(styles[1].len == 6);
        REQUIRE(styles[1].bitmask == Emphasis::UNDERL);
        REQUIRE(styles[2].start == 9);
        REQUIRE(styles[2].len == 2);
        REQUIRE(styles[2].bitmask == Emphasis::ITALIC);
    }
    SECTION("test 2")
    {
        TextMarkup markup("hello _world_");
        Text txt = markup.GetText();
        txt.SetEmphasisStyle(3, 6, Emphasis::UNDERL);
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 3);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 3);
        REQUIRE(styles[0].bitmask == Emphasis::NONE);
        REQUIRE(styles[1].start == 3);
        REQUIRE(styles[1].len == 6);
        REQUIRE(styles[1].bitmask == Emphasis::UNDERL);
        REQUIRE(styles[2].start == 9);
        REQUIRE(styles[2].len == 2);
        REQUIRE(styles[2].bitmask == Emphasis::ITALIC);
    }
}

TEST_CASE("Text - replace emphasis style", "[Text]")
{
    TextMarkup markup("hel*lo wo*rld");
    Text txt = markup.GetText();
    txt.SetEmphasisStyle(3, 5, Emphasis::ITALIC);
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 3);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 3);
    REQUIRE(styles[0].bitmask == Emphasis::NONE);
    REQUIRE(styles[1].start == 3);
    REQUIRE(styles[1].len == 5);
    REQUIRE(styles[1].bitmask == Emphasis::ITALIC);
    REQUIRE(styles[2].start == 8);
    REQUIRE(styles[2].len == 3);
    REQUIRE(styles[2].bitmask == Emphasis::NONE);
}

TEST_CASE("Text - set emphasis style, invalid start", "[Text]")
{
    TextMarkup markup("hello world");
    Text txt = markup.GetText();
    try
    {
        txt.SetEmphasisStyle(12, 1, Emphasis::BOLD);
        FAIL("Trying to set emphasis style with out of range start should throw std::out_of_range");
    }
    catch (std::out_of_range)
    {
    }
}

TEST_CASE("Text - set emphasis style, invalid length", "[Text]")
{
    TextMarkup markup("~hello *world*~");
    Text txt = markup.GetText();

    SECTION("len == 0")
    {
        txt.SetEmphasisStyle(0, 0, Emphasis::ITALIC);
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 6);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
        REQUIRE(styles[1].start == 6);
        REQUIRE(styles[1].len == 5);
        REQUIRE(styles[1].bitmask == (Emphasis::STRIKE | Emphasis::BOLD));
    }
    SECTION("len too long")
    {
        txt.SetEmphasisStyle(3, 9, Emphasis::ITALIC);
        std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
        REQUIRE(styles.size() == 2);
        REQUIRE(styles[0].start == 0);
        REQUIRE(styles[0].len == 3);
        REQUIRE(styles[0].bitmask == Emphasis::STRIKE);
        REQUIRE(styles[1].start == 3);
        REQUIRE(styles[1].len == 8);
        REQUIRE(styles[1].bitmask == Emphasis::ITALIC);
    }
}

TEST_CASE("Text - set emphasis style, compression", "[Text]")
{
    TextMarkup markup("hello *world*");
    Text txt = markup.GetText();
    txt.SetEmphasisStyle(6, 5, Emphasis::NONE);
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 1);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 11);
    REQUIRE(styles[0].bitmask == Emphasis::NONE);
}

TEST_CASE("Text - toggle emphasis style, no existing style", "[Text]")
{
    TextMarkup markup("hello world");
    Text txt = markup.GetText();
    txt.ToggleEmphasisStyle(3, 3, (Emphasis::BOLD | Emphasis::ITALIC));
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 3);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 3);
    REQUIRE(styles[0].bitmask == Emphasis::NONE);
    REQUIRE(styles[1].start == 3);
    REQUIRE(styles[1].len == 3);
    REQUIRE(styles[1].bitmask == (Emphasis::BOLD | Emphasis::ITALIC));
    REQUIRE(styles[2].start == 6);
    REQUIRE(styles[2].len == 5);
    REQUIRE(styles[2].bitmask == Emphasis::NONE);
}

TEST_CASE("Text - toggle emphasis style, existing style", "[Text]")
{
    TextMarkup markup("*hello* world");
    Text txt = markup.GetText();
    txt.ToggleEmphasisStyle(3, 5, Emphasis::ITALIC);
    std::vector<TextEmphasis> styles = txt.GetEmphasisStyles();
    REQUIRE(styles.size() == 4);
    REQUIRE(styles[0].start == 0);
    REQUIRE(styles[0].len == 3);
    REQUIRE(styles[0].bitmask == Emphasis::BOLD);
    REQUIRE(styles[1].start == 3);
    REQUIRE(styles[1].len == 2);
    REQUIRE(styles[1].bitmask == (Emphasis::BOLD | Emphasis::ITALIC));
    REQUIRE(styles[2].start == 5);
    REQUIRE(styles[2].len == 3);
    REQUIRE(styles[2].bitmask == Emphasis::ITALIC);
    REQUIRE(styles[3].start == 8);
    REQUIRE(styles[3].len == 3);
    REQUIRE(styles[3].bitmask == Emphasis::NONE);
}

TEST_CASE("Text - set new metadata", "[Text]")
{
    TextMetadata expected;
    expected.size = TextSize::S2;
    expected.outline_color = { 10, 10, 10, 10 };
    expected.fill_color = { 100, 100, 100, 100 };
    expected.bg_color = { 200, 200, 200, 200 };
    TextMarkup markup("hello world");
    Text txt = markup.GetText();
    txt.SetMetadata(0, 11, expected.size, expected.outline_color, expected.fill_color, expected.bg_color,
        MetadataChangeBits::ALL_CHANGED);
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0] == expected);
}

TEST_CASE("Text - change metadata", "[Text]")
{
    TextMarkup markup("!2hello !3world");
    Text txt = markup.GetText();
    txt.SetMetadata(3, 6, TextSize::S4, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 },
        MetadataChangeBits::ALL_CHANGED);
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 3);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 3);
    REQUIRE(metadata[0].size == TextSize::S2);
    REQUIRE(metadata[1].start == 3);
    REQUIRE(metadata[1].len == 6);
    REQUIRE(metadata[1].size == TextSize::S4);
    REQUIRE(metadata[2].start == 9);
    REQUIRE(metadata[2].len == 2);
    REQUIRE(metadata[2].size == TextSize::S3);
}

TEST_CASE("Text - set metadata, invalid start", "[Text]")
{
    TextMarkup markup("hello world");
    Text txt = markup.GetText();
    try
    {
        txt.SetMetadata(12, 1, TextSize::S2, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 },
            MetadataChangeBits::ALL_CHANGED);
        FAIL("Trying to set metadata with out of range start should throw std::out_of_range");
    }
    catch (std::out_of_range)
    {
    }
}

TEST_CASE("Text - set metadata, invalid length", "[Text]")
{
    TextMarkup markup("!2hello world");
    Text txt = markup.GetText();

    SECTION("len == 0")
    {
        txt.SetMetadata(0, 0, TextSize::S3, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 },
            MetadataChangeBits::ALL_CHANGED);
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 1);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 11);
        REQUIRE(metadata[0].size == TextSize::S2);
    }
    SECTION("len too long")
    {
        txt.SetMetadata(3, 9, TextSize::S3, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 },
            MetadataChangeBits::ALL_CHANGED);
        std::vector<TextMetadata> metadata = txt.GetMetadata();
        REQUIRE(metadata.size() == 2);
        REQUIRE(metadata[0].start == 0);
        REQUIRE(metadata[0].len == 3);
        REQUIRE(metadata[0].size == TextSize::S2);
        REQUIRE(metadata[1].start == 3);
        REQUIRE(metadata[1].len == 8);
        REQUIRE(metadata[1].size == TextSize::S3);
    }
}

TEST_CASE("Text - set metadata, compression", "[Text]")
{
    TextMarkup markup("hello !2world");
    Text txt = markup.GetText();
    txt.SetMetadata(6, 5, TextSize::S1, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 },
        MetadataChangeBits::ALL_CHANGED);
    std::vector<TextMetadata> metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0].size == TextSize::S1);
}

TEST_CASE("Text - set metadata, overloaded functions", "[Text]")
{
    TextMetadata expected;
    std::vector<TextMetadata> metadata;
    TextMarkup markup("hello world");
    Text txt = markup.GetText();

    expected.size = TextSize::S2;
    txt.SetMetadataSize(0, 11, expected.size);
    metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0] == expected);

    expected.outline_color = { 100, 100, 100, 100 };
    txt.SetMetadataOutlineColor(0, 11, expected.outline_color);
    metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0] == expected);

    expected.fill_color = { 100, 100, 100, 100 };
    txt.SetMetadataFillColor(0, 11, expected.fill_color);
    metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0] == expected);

    expected.bg_color = { 100, 100, 100, 100 };
    txt.SetMetadataBgColor(0, 11, expected.bg_color);
    metadata = txt.GetMetadata();
    REQUIRE(metadata.size() == 1);
    REQUIRE(metadata[0].start == 0);
    REQUIRE(metadata[0].len == 11);
    REQUIRE(metadata[0] == expected);
}

} // namespace txt
