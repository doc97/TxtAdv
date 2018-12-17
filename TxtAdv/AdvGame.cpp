#include "AdvGame.h"
#include <iostream>
#include <regex>

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
        [this](const ResponseMatch& match) { this->Exit(); }
    );
    handlers.emplace_back(
        [](const std::string& input) { return input == "start"; },
        [this](const ResponseMatch& match) { this->StoryNext(); }
    );
    m_branch.AddPoint("Welcome to TxtAdv!", handlers);
}

void AdvGame::InitPointTwo()
{
    std::vector<ResponseHandler> handlers;
    handlers.emplace_back(
        [](const std::string& input) { return ResponseMatch(input == "exit"); },
        [this](const ResponseMatch& match) { this->Exit(); }
    );
    handlers.emplace_back(
        [](const std::string& input)
        {
            std::smatch match;
            std::regex rgx("(.*)=(.*)");
            std::vector<std::string> captures;
            if (std::regex_match(input, match, rgx))
                return ResponseMatch(true, { match.str(1), match.str(2) });
            return ResponseMatch(false);
        },
        [this](const ResponseMatch& match)
        {
            this->GetState().SetString(match.GetCapture(0), match.GetCapture(1));
        }
    );
    std::vector<std::function<std::string()>> markup;
    markup.emplace_back([this]() { return this->GetState().ReadString("name", "<unknown>"); });
    m_branch.AddPoint("Your name: $0\n", markup, handlers);
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

GameState& AdvGame::GetState()
{
    return m_state;
}

IO* AdvGame::GetIO() const
{
    return m_io;
}
