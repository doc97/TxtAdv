/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include "IO.h"

namespace txt
{

class Prompt
{
public:
    Prompt(IO* io);
    ~Prompt();

    std::string PromptInput();
    void SetPrompt(const std::string& prompt);
private:
    IO* m_io;
    std::string m_input;
    std::string m_prompt;
};

} // namespace txt
