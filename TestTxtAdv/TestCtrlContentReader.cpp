/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "CtrlContentReader.h"

namespace txt
{

TEST_CASE("CtrlContentReader - all fields correct", "[CtrlContentReader]")
{
    std::stringstream ss("Title, file.lua, matcher_func, action_func");

    CtrlContentReader reader;
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 1);
    REQUIRE(info.ctrl_content["Title"][0].storypoint == "Title");
    REQUIRE(info.ctrl_content["Title"][0].script == "file.lua");
    REQUIRE(info.ctrl_content["Title"][0].matcher_func == "matcher_func");
    REQUIRE(info.ctrl_content["Title"][0].action_func == "action_func");
}

TEST_CASE("CtrlContentReader - invalid file", "[CtrlContentReader]")
{
    try
    {
        CtrlContentReader reader;
        CtrlContentInfo info = reader.Read("DoesNotExist.ctrl");
        FAIL("Trying to read a non-existent file should throw an std::runtime_error");
    }
    catch (std::runtime_error)
    {
    }
}

TEST_CASE("CtrlContentReader - missing field", "[CtrlContentReader]")
{
    CtrlContentReader reader;

    SECTION("missing one field")
    {
        std::stringstream ss("Title,test.lua,matcher_func");
        try
        {
            CtrlContentInfo info = reader.Read(ss);
            FAIL("A file format error should throw an std::runtime_error");
        }
        catch (std::runtime_error) {}
    }
    SECTION("missing two fields")
    {
        std::stringstream ss("Title,test.lua");
        try
        {
            CtrlContentInfo info = reader.Read(ss);
            FAIL("A file format error should throw an std::runtime_error");
        }
        catch (std::runtime_error) {}
    }
}

TEST_CASE("CtrlContentReader - empty story point ID field", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss(",test.lua,matches_func,action_func");
    try
    {
        CtrlContentInfo info = reader.Read(ss);
        FAIL("An empty story point ID field should throw an std::runtime_error");
    }
    catch (std::runtime_error) {}
}

TEST_CASE("CtrlContentReader - empty script field", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss("Title,,matches_func,action_func");
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 0);
}

TEST_CASE("CtrlContentReader - empty matcher function field", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss("Title,test.lua,,action_func");
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 0);
}

TEST_CASE("CtrlContentReader - empty action function field", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss("Title,test.lua,matcher_func, ");
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 0);
}

TEST_CASE("CtrlContentReader - multiple definitions", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss;
    ss << "Title,test.lua,matcher_func,action_func\n";
    ss << "Title,test.lua,matcher2_func,action2_func\n";
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 2);
    REQUIRE(info.ctrl_content["Title"][0].matcher_func == "matcher_func");
    REQUIRE(info.ctrl_content["Title"][0].action_func == "action_func");
    REQUIRE(info.ctrl_content["Title"][1].matcher_func == "matcher2_func");
    REQUIRE(info.ctrl_content["Title"][1].action_func == "action2_func");
}

TEST_CASE("CtrlContentReader - empty new lines skipped", "[CtrlContentReader]")
{
    CtrlContentReader reader;
    std::stringstream ss;
    ss << "Title,test.lua,matcher_func,action_func\n";
    ss << "\n";
    ss << "Title,test.lua,matcher2_func,action2_func\n";
    CtrlContentInfo info = reader.Read(ss);
    REQUIRE(info.ctrl_content["Title"].size() == 2);
    REQUIRE(info.ctrl_content["Title"][0].matcher_func == "matcher_func");
    REQUIRE(info.ctrl_content["Title"][0].action_func == "action_func");
    REQUIRE(info.ctrl_content["Title"][1].matcher_func == "matcher2_func");
    REQUIRE(info.ctrl_content["Title"][1].action_func == "action2_func");
}

} // namespace txt
