/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Prompt.h"
#include <iostream>

namespace txt
{

Prompt::Prompt(IO* io)
    : m_io(io)
{
}

Prompt::~Prompt()
{
}

std::string Prompt::PromptInput()
{
    m_io->Write(m_prompt);
    m_io->GetLine(m_input);
    return m_input;
}

void Prompt::SetPrompt(const std::string& prompt)
{
    m_prompt = prompt;
}

} // namespace txt
