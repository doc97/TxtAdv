/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StoryLoader.h"

namespace txt
{

TEST_CASE("StoryLoader - load non-existent file", "[StoryLoader]")
{
    StoryLoader loader;
    try
    {
        std::vector<StoryPoint> points = loader.Load("Content/doesnotexist.txt");
        FAIL("Loading a non-existent file should throw a std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
}

TEST_CASE("StoryLoader - load file with invalid format", "[StoryLoader]")
{
    StoryLoader loader;
    try
    {
        std::vector<StoryPoint> points = loader.Load("Content/invalid.txt");
        FAIL("Loading an invalid file should throw a std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
}

TEST_CASE("StoryLoader - load valid txt", "[StoryLoader]")
{
    StoryLoader loader;
    SECTION("file 1")
    {
        std::vector<StoryPoint> points = loader.Load("Content/valid1.txt");
        REQUIRE(points.size() == 1);
        REQUIRE(points[0].GetName() == "Valid 1");
        REQUIRE(points[0].GetTextStr() == "I am a valid txt file");
        REQUIRE(points[0].GetHandlerCount() == 1);
    }
    SECTION("file 2")
    {
        std::vector<StoryPoint> points = loader.Load("Content/valid2.txt");
        REQUIRE(points.size() == 1);
        REQUIRE(points[0].GetName() == "Valid 2");
        REQUIRE(points[0].GetTextStr() == "I am also a valid txt file");
        REQUIRE(points[0].GetHandlerCount() == 1);
    }
}

TEST_CASE("StoryLoader - multiple story points", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/multi_story.txt");
    REQUIRE(points.size() == 2);
    REQUIRE(points[0].GetName() == "Multi 1");
    REQUIRE(points[0].GetTextStr() == "I am one of the story points.");
    REQUIRE(points[0].GetHandlerCount() == 1);
    REQUIRE(points[1].GetName() == "Multi 2");
    REQUIRE(points[1].GetTextStr() == "I am the other one.");
    REQUIRE(points[1].GetHandlerCount() == 1);
}

TEST_CASE("StoryLoader - multiple handlers", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/multi_handler.txt");
    REQUIRE(points.size() == 1);
    REQUIRE(points[0].GetHandlerCount() == 2);
}

TEST_CASE("StoryLoader - newlines", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/multiline.txt");
    REQUIRE(points.size() == 1);
    REQUIRE(points[0].GetTextStr() == "I am a story point with multiple lines.\nIsn't this very cool?");
}

TEST_CASE("StoryLoader - escape character", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/escape.txt");
    REQUIRE(points.size() == 1);
    REQUIRE(points[0].GetTextStr() == "I am an *escaped string*");
}

TEST_CASE("StoryLoader - comments", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/comments.txt");
    REQUIRE(points.size() == 2);
    REQUIRE(points[0].GetName() == "Hello world");
    REQUIRE(points[0].GetTextStr() == "Lorem");
    REQUIRE(points[1].GetName() == "Hello");
    REQUIRE(points[1].GetTextStr() == "ipsum");
}

TEST_CASE("StoryLoader - style file", "[StoryLoader]")
{
    StoryLoader loader;
    std::vector<StoryPoint> points = loader.Load("Content/style.txt");
    REQUIRE(points.size() == 1);

    Text text = points[0].GetText();
    std::vector<TextEmphasis> emphasis = text.GetEmphasisStyles();
    std::vector<TextMetadata> metadata = text.GetMetadata();
    REQUIRE(emphasis.size() == 3);
    REQUIRE(emphasis[0].bitmask == Emphasis::NONE);
    REQUIRE(emphasis[1].start == 5);
    REQUIRE(emphasis[1].len == 10);
    REQUIRE(emphasis[1].bitmask == Emphasis::BOLD);
    REQUIRE(emphasis[2].bitmask == Emphasis::NONE);
    REQUIRE(metadata.size() == 3);
    REQUIRE(metadata[0].size == TextSize::S1);
    REQUIRE(metadata[1].start == 23);
    REQUIRE(metadata[1].len == 4);
    REQUIRE(metadata[1].size == TextSize::S2);
    REQUIRE(metadata[2].size == TextSize::S1);
}

} // namespace txt
