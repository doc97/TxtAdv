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
    m_response.AddHandler(
        [](const std::string& input) { return input == "exit"; },
        [this]() { this->Exit(); }
    );
    m_response.AddHandler(
        [](const std::string& input) { return input == "hello"; },
        [this]() { this->GetIO()->WriteLine("world"); }
    );

    InitStory();
}

void AdvGame::InitStory()
{
    InitPointOne();
    InitPointTwo();
}

void AdvGame::InitPointOne()
{
    std::vector<ResponseHandler> handlers;
    handlers.emplace_back(
        [](const std::string& input) { return input == "exit"; },
        [this]() { this->Exit(); }
    );
    handlers.emplace_back(
        [](const std::string& input) { return input == "start"; },
        [this]() { this->StoryNext(); }
    );
    m_branch.AddPoint("Welcome to TxtAdv!", handlers);
}

void AdvGame::InitPointTwo()
{
    std::vector<ResponseHandler> handlers;
    handlers.emplace_back(
        [](const std::string& input) { return input == "exit"; },
        [this]() { this->Exit(); }
    );
    m_branch.AddPoint("This is you: ...", handlers);
}

void AdvGame::Update()
{
    m_response.ClearHandlers();
    m_response.AddHandlers(m_branch.GetHead()->GetHandlers());

    m_io->WriteLine(m_branch.GetHead()->GetText());
    std::string input = m_prompt.PromptInput();
    m_response.HandleInput(input);
}

void AdvGame::StoryNext()
{
    m_branch.Next();
}

void AdvGame::StoryPrev()
{
    m_branch.Prev();
}

IO* AdvGame::GetIO() const
{
    return m_io;
}
