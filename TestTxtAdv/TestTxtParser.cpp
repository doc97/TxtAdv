/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "TxtParser.h"
#include "LambdaExpression.h"

namespace txt
{

TEST_CASE("TxtParser - no variables", "[TxtParser]")
{
    std::string text1 = "no variables here";
    std::string text2 = "or here";
    GameState state;
    TxtParser parser(&state);
    REQUIRE(parser.ParseText(text1) == text1);
    REQUIRE(parser.ParseText(text2) == text2);
}

TEST_CASE("TxtParser - simple variable", "[TxtParser]")
{
    GameState state;
    state.SetString("first_name", "Foo");
    state.SetString("middle_name", "Bar");
    state.SetString("last_name", "Foobar");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{s_first_name}") == "Foo");
    REQUIRE(parser.ParseText("{s_middle_name}") == "Bar");
    REQUIRE(parser.ParseText("{s_last_name}") == "Foobar");
}

TEST_CASE("TxtParser - string variable", "[TxtParser]")
{
    GameState state;
    state.SetString("name", "Foo");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{s_unknown}") == "<unknown>");
    REQUIRE(parser.ParseText("{a_invalid}") == "{a_invalid}");
    REQUIRE(parser.ParseText("{name}") == "{name}");
}

TEST_CASE("TxtParser - float variable", "[TxtParser]")
{
    GameState state;
    state.SetFloat("value1", 1.5f);
    state.SetFloat("value2", 2.256f);
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{value1}") == "{value1}");
    REQUIRE(parser.ParseText("{f_value1}") == "1.50");
    REQUIRE(parser.ParseText("{f_value2}") == "2.26");
}

TEST_CASE("TxtParser - int variable", "[TxtParser]")
{
    GameState state;
    state.SetInt("value1", -1);
    state.SetInt("value2", 2);
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{value1}") == "{value1}");
    REQUIRE(parser.ParseText("{i_value1}") == "-1");
    REQUIRE(parser.ParseText("{i_value2}") == "2");
}

TEST_CASE("TxtParser - expression variable", "[TxtParser]")
{
    GameState state;
    TxtParser parser(&state);
    parser.AddExpression("expr1", std::make_unique<LambdaExpression>([]() { return "foo"; }));
    parser.AddExpression("expr2", std::make_unique<LambdaExpression>([]() { return "bar"; }));
    REQUIRE(parser.ParseText("{expr1}") == "{expr1}");
    REQUIRE(parser.ParseText("{x_expr1}") == "foo");
    REQUIRE(parser.ParseText("{x_expr2}") == "bar");
    REQUIRE(parser.ParseText("{x_expr1}{x_expr2}") == "foobar");
}

TEST_CASE("TxtParser - variable type", "[TxtParser]")
{
    GameState state;
    state.SetInt("value", 1);
    state.SetFloat("value", 1.5f);
    state.SetString("value", "Foo");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{i_value}") == "1");
    REQUIRE(parser.ParseText("{f_value}") == "1.50");
    REQUIRE(parser.ParseText("{s_value}") == "Foo");
}

TEST_CASE("TxtParser - insert variable", "[TxtParser]")
{
    GameState state;
    state.SetString("name", "Foo");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{s_name} Bar") == "Foo Bar");
    REQUIRE(parser.ParseText("Bar {s_name}") == "Bar Foo");
    REQUIRE(parser.ParseText("{s_name}Bar") == "FooBar");
    REQUIRE(parser.ParseText("Bar{s_name}") == "BarFoo");
}

TEST_CASE("TxtParser - recursive variable", "[TxtParser]")
{
    GameState state;
    state.SetString("rgx", "s_name");
    state.SetString("name", "Foo");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{s_rgx}") == "s_name");
    REQUIRE(parser.ParseText("{{s_rgx}}") == "Foo");
}

TEST_CASE("TxtParser - recursive depth", "[TxtParser]")
{
    GameState state;
    state.SetString("rec1", "{s_rec2}");
    state.SetString("rec2", "{s_rec1}");
    TxtParser parser(&state);

    // Max recursive depth is 8
    REQUIRE(parser.ParseText("{s_rec1}") == "{s_rec1}");
    REQUIRE(parser.ParseText("{s_rec2}") == "{s_rec2}");
}

TEST_CASE("TxtParser - dynamic, recursive variable expressions", "[TxtParser]")
{
    GameState state;
    state.SetString("var_type", "s");
    state.SetString("var_animal", "dog");
    state.SetString("var_property", "name");
    state.SetString("dog_name", "Fido");
    state.SetString("expr", "{s_var_type}_{s_var_animal}_{s_var_property}");
    TxtParser parser(&state);
    REQUIRE(parser.ParseText("{{s_var_type}_{s_var_animal}_{s_var_property}}") == "Fido");
    REQUIRE(parser.ParseText("{{s_expr}}") == "Fido");
}

} // namespace txt
