#include "AdvGame.h"
#include <iostream>

AdvGame::AdvGame(IO* io)
    : m_io(io), m_prompt(m_io)
{
}

AdvGame::~AdvGame()
{
}

void AdvGame::Init()
{
    m_prompt.SetPrompt("> ");
    m_response.AddHandler("exit", [this]() { this->Exit(); });
    m_response.AddHandler("hello", [this]() { this->GetIO()->WriteLine("world"); });
}

void AdvGame::Update()
{
    std::string input = m_prompt.PromptInput();
    m_response.HandleInput(input);
}

IO* AdvGame::GetIO() const
{
    return m_io;
}
