#include "AdvGame.h"
#include <iostream>

AdvGame::AdvGame(IO* io)
    : m_prompt(io)
{
}

AdvGame::~AdvGame()
{
}

void AdvGame::Init()
{
    m_prompt.SetPrompt("> ");
}

void AdvGame::Update()
{
    std::string input = m_prompt.PromptInput();
    m_response.HandleInput(input);
}
