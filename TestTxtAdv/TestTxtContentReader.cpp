/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "TxtContentReader.h"

namespace txt
{

TEST_CASE("TxtContentReader - All fields correct", "[TxtContentReader]")
{
    std::stringstream ss;
    ss << "Ctrl: test.ctrl\n";
    ss << "Style: test.style\n";
    ss << "\n";
    ss << "Story: hello\n";
    ss << "  text\n";

    TxtContentReader reader;
    TxtContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_filename == "test.ctrl");
    REQUIRE(info.style_filename == "test.style");
    REQUIRE(info.story_points.size() == 1);
    REQUIRE(info.story_points[0].GetName() == "hello");
    REQUIRE(info.story_points[0].GetTextStr() == "text");
}

TEST_CASE("TxtContentReader - invalid file", "[TxtContentReader]")
{
    try
    {
        TxtContentReader reader;
        TxtContentInfo info = reader.Read("DoesNotExist.txt");
        FAIL("Trying to read a non-existent file should throw a std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
}

TEST_CASE("TxtContentReader - Ctrl field", "[TxtContentReader]")
{
    TxtContentReader reader;
    std::stringstream ss;

    SECTION("missing completely")
    {
        ss << "Story: hello\n";
        ss << "  text\n";
        try
        {
            TxtContentInfo info = reader.Read(ss);
            FAIL("Missing Ctrl-field should throw a std::runtime_error");
        }
        catch (std::runtime_error)
        {
        }
    }
    SECTION("wrong order")
    {
        ss << "Story: hello\n";
        ss << "  text\n";
        ss << "Ctrl: test.ctrl\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points.size() == 0);
    }
}

TEST_CASE("TxtContentReader - Style field, before ctrl field", "[TxtContentReader]")
{
    std::stringstream ss;
    ss << "Style: test.style\n";
    ss << "Ctrl: test.ctrl\n";

    TxtContentReader reader;
    TxtContentInfo info = reader.Read(ss);
    REQUIRE(info.style_filename.empty());
}

TEST_CASE("TxtContentReader - story spacing", "[TxtContentReader]")
{
    TxtContentReader reader;
    std::stringstream ss;
    ss << "Ctrl: test.ctrl\n";

    SECTION("single story, no spacing")
    {
        ss << "Story: hello\n";
        ss << "  text\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points.size() == 0);
    }
    SECTION("multiple stories no spacing between")
    {
        ss << "\n";
        ss << "Story: hello\n";
        ss << "  text\n";
        ss << "Story: foo\n";
        ss << "  bar\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points.size() == 2);
        REQUIRE(info.story_points[0].GetTextStr() == "text");
        REQUIRE(info.story_points[1].GetTextStr() == "bar");
    }
}

TEST_CASE("TxtContentReader - story text indentation", "[TxtContentReader]")
{
    TxtContentReader reader;
    std::stringstream ss;
    ss << "Ctrl: test.ctrl\n";
    ss << "\n";
    ss << "Story: hello\n";

    SECTION("no indentation")
    {
        ss << "text\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points[0].GetTextStr() == "");
    }
    SECTION("too little indentation")
    {
        ss << " text\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points[0].GetTextStr() == "");
    }
    SECTION("correct indendation")
    {
        ss << "  text\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points[0].GetTextStr() == "text");
    }
    SECTION("too much indentation")
    {
        ss << "   text\n";
        TxtContentInfo info = reader.Read(ss);
        REQUIRE(info.story_points[0].GetTextStr() == "text");
    }
}

TEST_CASE("TxtContentReader - story text spacing", "[TxtContentReader]")
{
    TxtContentReader reader;
    std::stringstream ss;
    ss << "Ctrl: test.ctrl\n";
    ss << "\n";
    ss << "Story: hello\n";
    ss << "  First line\n";
    ss << "  \n";
    ss << "  new line\n";

    TxtContentInfo info = reader.Read(ss);
    REQUIRE(info.story_points[0].GetTextStr() == "First line\n\nnew line");
}

} // namespace txt
