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

} // namespace txt
