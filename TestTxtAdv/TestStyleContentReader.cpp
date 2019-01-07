/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "StyleContentReader.h"

namespace txt
{

TEST_CASE("StyleContentReader - invalid file", "[StyleContentReader]")
{
    try
    {
        StyleContentReader reader;
        TextStyleSheet sheet = reader.Read("DoesNotExist.style");
        FAIL("Trying to read a non-existent file should throw a std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
}

TEST_CASE("StyleContentReader - invalid style name, starts with number", "[StyleContentReader]")
{
    StyleContentReader reader;
    std::stringstream ss;

    SECTION("test 1")
    {
        ss << "0invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle("0invalid"));
    }
    SECTION("test 2")
    {
        ss << "1invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle("1invalid"));
    }
}

TEST_CASE("StyleContentReader - invalid style name, starts with special character", "[StyleContentReader]")
{
    StyleContentReader reader;
    std::stringstream ss;

    SECTION("!")
    {
        ss << "!invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle("!invalid"));
    }
    SECTION("#")
    {
        ss << "#invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle("!invalid"));
    }
    SECTION(">")
    {
        ss << ">invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle(">invalid"));
    }
    SECTION("<")
    {
        ss << "<invalid\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(!sheet.HasStyle("<invalid"));
    }
}

TEST_CASE("StyleContentReader - valid style name", "[StyleContentReader]")
{
    StyleContentReader reader;
    std::stringstream ss;
    ss << "a\n";
    TextStyleSheet sheet = reader.Read(ss);
    REQUIRE(sheet.HasStyle("a"));
}

TEST_CASE("StyleContentReader - indentation", "[StyleContentReader]")
{
    StyleContentReader reader;
    std::stringstream ss;

    SECTION("No indentation")
    {
        ss << "a\n";
        ss << "emphasis: bold\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(sheet.GetStyle("a").bitmask == Emphasis::NONE);
    }
    SECTION("too little indentation")
    {
        ss << "a\n";
        ss << " emphasis: bold\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(sheet.GetStyle("a").bitmask == Emphasis::NONE);
    }
    SECTION("correct indentation")
    {
        ss << "a\n";
        ss << "  emphasis: bold\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(sheet.GetStyle("a").bitmask == Emphasis::BOLD);
    }
    SECTION("too much indentation")
    {
        ss << "a\n";
        ss << "   emphasis: bold\n";
        TextStyleSheet sheet = reader.Read(ss);
        REQUIRE(sheet.GetStyle("a").bitmask == Emphasis::BOLD);
    }
}

} // namespace txt
