/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Prompt.h"
#include <iostream>

namespace txt
{

Prompt::Prompt()
{
}

Prompt::~Prompt()
{
}

std::string Prompt::PromptInput(IO& io)
{
    io.Write(m_prompt);
    io.GetLine(m_input);
    return m_input;
}

void Prompt::SetPrompt(const std::string& prompt)
{
    m_prompt = prompt;
}

} // namespace txt
