#include "Prompt.h"
#include <iostream>

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
