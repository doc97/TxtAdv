#include "catch.hpp"
#include "Prompt.h"
#include "IO.h"
#include <sstream>

class TestIO : public IO
{
public:
    TestIO(const std::string& input) : m_input(input) {}

    std::string m_input;
    std::string m_output;

    void Write(const std::string& string)
    {
        m_output = string;
    }

    void WriteLine(const std::string& string)
    {
        std::ostringstream oss;
        oss << string << std::endl;
        m_output = oss.str();
    }

    void GetLine(std::string& string)
    {
        string = m_input;
    }
};

TEST_CASE("Prompt")
{
    TestIO io("line");
    Prompt prompt(&io);

    SECTION("test input prompt")
    {
        std::string result = prompt.PromptInput();
        REQUIRE(result == "line");
    }
    SECTION("test prompt")
    {
        prompt.SetPrompt("$ ");
        prompt.PromptInput();
        REQUIRE(io.m_output == "$ ");
    }
}