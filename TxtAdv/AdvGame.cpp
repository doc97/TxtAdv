#include "AdvGame.h"
#include <iostream>

AdvGame::AdvGame()
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
    m_handler.HandleInput(input);
}
