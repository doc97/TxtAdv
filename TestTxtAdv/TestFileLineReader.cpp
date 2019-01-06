/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "FileLineReader.h"

namespace txt
{

TEST_CASE("FileLineReader - read closed stream", "[FileLineReader]")
{
    std::string line;
    std::ifstream file;
    FileLineReader reader;
    REQUIRE(!reader.NextLine(file, line));
}

TEST_CASE("FileLineReader - read not commented file", "[FileLineReader]")
{
    std::string line;
    std::ifstream file("Content/valid1.txt");
    FileLineReader reader;
    size_t lineCount = 0;
    while (reader.NextLine(file, line))
        ++lineCount;
    REQUIRE(lineCount == 4);
}

TEST_CASE("FileLineReader - read commented file", "[FileLineReader]")
{
    std::string line;
    std::ifstream file("Content/comments.txt");
    FileLineReader reader;
    size_t lineCount = 0;
    while (reader.NextLine(file, line))
        ++lineCount;
    REQUIRE(lineCount == 8);
}

} // namespace txt
