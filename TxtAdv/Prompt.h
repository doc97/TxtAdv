#pragma once

#include <string>

class Prompt
{
public:
    Prompt();
    ~Prompt();

    std::string PromptInput();
    void SetPrompt(const std::string& prompt);
private:
    std::string m_input;
    std::string m_prompt;
};

