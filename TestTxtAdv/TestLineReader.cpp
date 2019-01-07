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

} // namespace txt
