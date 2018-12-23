/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "catch.hpp"
#include "Prompt.h"
#include "IO.h"
#include <sstream>

namespace txt
{

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

TEST_CASE("Prompt", "[Prompt]")
{
    TestIO io("line");
    Prompt prompt(&io);

    SECTION("test prompt")
    {
        prompt.SetPrompt("$ ");
        std::string result = prompt.PromptInput();
        REQUIRE(io.m_output == "$ ");
        REQUIRE(result == "line");
    }
}

} // namespace txt
