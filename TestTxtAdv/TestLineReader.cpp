/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "LineReader.h"
#include <fstream>

namespace txt
{

TEST_CASE("LineReader - read closed stream", "[LineReader]")
{
    std::string line;
    std::ifstream file;
    LineReader reader;
    REQUIRE(!reader.NextLine(file, line));
}

TEST_CASE("LineReader - read not commented file", "[LineReader]")
{
    std::string line;
    std::ifstream file("Content/valid1.txt");
    LineReader reader;
    size_t lineCount = 0;
    while (reader.NextLine(file, line))
        ++lineCount;
    REQUIRE(lineCount == 4);
}

TEST_CASE("LineReader - read commented file", "[LineReader]")
{
    std::string line;
    std::ifstream file("Content/comments.txt");
    LineReader reader;
    size_t lineCount = 0;
    while (reader.NextLine(file, line))
        ++lineCount;
    REQUIRE(lineCount == 8);
}

TEST_CASE("LineReader - read not commented string", "[LineReader]")
{
    std::string line;
    std::stringstream ss;
    LineReader reader;
    size_t lineCount = 0;

    SECTION("normal")
    {
        ss << "Hello\n" << "world\n" << "    foobar\nbye";
        while (reader.NextLine(ss, line))
            ++lineCount;
        REQUIRE(lineCount == 4);
    }
    SECTION("empty lines")
    {
        ss << "\n\n\n";
        while (reader.NextLine(ss, line))
            ++lineCount;
        REQUIRE(lineCount == 3);
    }
}

TEST_CASE("LineReader - read commented string", "[LineReader]")
{
    std::string line;
    std::stringstream ss;
    LineReader reader;
    size_t lineCount = 0;

    ss << "Hello\n";
    ss << "// I am a comment\n";
    ss << "/* I am a \nmultiline comment*/\n";
    ss << "  // I am a comment but this line counts\n";
    ss << "  /* so does this */\n";

    while (reader.NextLine(ss, line))
        ++lineCount;
    REQUIRE(lineCount == 3);
}

} // namespace txt
