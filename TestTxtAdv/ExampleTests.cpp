/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"

struct Subject
{
    Subject() : m_value(1) {}
    int m_value;
};
TEST_CASE("Simple example")
{
    Subject subj;

    SECTION("First section, passes")
    {
        REQUIRE(subj.m_value == 1);
    }
}