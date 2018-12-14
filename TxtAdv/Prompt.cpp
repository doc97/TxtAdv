#include "Prompt.h"
#include <iostream>

Prompt::Prompt()
{
}

Prompt::~Prompt()
{
}

std::string Prompt::PromptInput()
{
    std::cout << m_prompt;
    std::getline(std::cin, m_input);
    return m_input;
}

void Prompt::SetPrompt(const std::string& prompt)
{
    m_prompt = prompt;
}
