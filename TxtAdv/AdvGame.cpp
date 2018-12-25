/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "AdvGame.h"
#include <iostream>
#include <regex>
#include <sstream>
#include "LambdaResponseHandler.h"
#include "LuaResponseHandler.h"
#include "LuaGameState.h"
#include "LuaStoryBranch.h"

namespace txt
{

AdvGame::AdvGame(IO* io)
    : m_io(io), m_prompt(m_io)
{
}

AdvGame::~AdvGame()
{
}

void AdvGame::Init()
{
    InitLua();
    InitMisc();
    InitStory();
    m_response.AddHandlers(m_branch.GetHead()->GetHandlers());
}

void AdvGame::InitLua()
{
    m_manager.RegisterClass<LuaGameState>();
    m_manager.RegisterClass<LuaStoryBranch>();
    m_manager.PushObject(new LuaGameState(&m_state), "state", true);
    m_manager.PushObject(new LuaStoryBranch(&m_branch), "story", true);
}

void AdvGame::InitMisc()
{
    m_prompt.SetPrompt("> ");
}

void AdvGame::InitStory()
{
    InitPointOne();
    InitPointTwo();
    InitPointThree();
}

void AdvGame::InitPointOne()
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return input == "exit"; },
        [this](const ResponseMatch& match) { this->Exit(); }
    ));
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return input == "next"; },
        [this](const ResponseMatch& match) { this->GetStory().Next(); }
    ));
    m_branch.AddPoint("Welcome to TxtAdv!", {}, handlers);
}

void AdvGame::InitPointTwo()
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return ResponseMatch(input == "exit"); },
        [this](const ResponseMatch& match) { this->Exit(); }
    ));
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return input == "next"; },
        [this](const ResponseMatch& match) { this->GetStory().Next(); }
    ));
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input)
        {
            std::smatch match;
            std::regex rgx("(\\w*) ?(\\w+)\\s*=\\s*(\\w*)");
            std::vector<std::string> captures;
            if (std::regex_match(input, match, rgx))
            {
                std::vector<std::string> captures;
                for (size_t i = 1; i < match.size(); ++i)
                    captures.push_back(match.str(i));
                return ResponseMatch(true, captures);
            }
            return ResponseMatch(false);
        },
        [this](const ResponseMatch& match)
        {
            std::string type = match.GetCapture(0);
            std::string key = match.GetCapture(1);
            std::string val = match.GetCapture(2);
            try
            {
                if (type == "int")
                    this->GetState().SetInt(key, std::stoi(val, nullptr, 10));
                else if (type == "float")
                    this->GetState().SetFloat(key, std::stof(val));
                else
                    this->GetState().SetString(key, val);
            }
            catch (std::invalid_argument)
            {
                this->GetIO()->WriteLine("Invalid type!\n---");
            }
        }
    ));
    std::vector<std::function<std::string()>> markup;
    markup.emplace_back([this]()
    {
        std::unordered_map<std::string, int> intMap = this->GetState().GetAllInts();
        std::unordered_map<std::string, float> floatMap = this->GetState().GetAllFloats();
        std::unordered_map<std::string, std::string> strMap = this->GetState().GetAllStrings();
        std::unordered_map<std::string, int>::iterator iIt = intMap.begin();
        std::unordered_map<std::string, float>::iterator fIt = floatMap.begin();
        std::unordered_map<std::string, std::string>::iterator sIt = strMap.begin();
        std::stringstream ss;

        ss << "(ints)" << std::endl;
        for (; iIt != intMap.end(); ++iIt)
            ss << iIt->first << ": " << iIt->second << std::endl;
        ss << "(floats)" << std::endl;
        for (; fIt != floatMap.end(); ++fIt)
            ss << fIt->first << ": " << fIt->second << std::endl;
        ss << "(strings)" << std::endl;
        for (; sIt != strMap.end(); ++sIt)
            ss << sIt->first << ": " << sIt->second << std::endl;
        return ss.str();
    });
    m_branch.AddPoint("Current state:\n$0", markup, handlers);
}

void AdvGame::InitPointThree()
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    // Showing that combining response handlers work
    handlers.emplace_back(std::make_shared<LambdaResponseHandler>(
        [](const std::string& input) { return ResponseMatch(input == "exit"); },
        [this](const ResponseMatch& match) { this->Exit(); }
    ));
    handlers.emplace_back(std::make_shared<LuaResponseHandler>(
        &m_manager,
        "LUA/3.lua"
    ));
    std::vector<std::function<std::string()>> markup;
    markup.emplace_back([this]()
    {
        return this->GetState().ReadString("text", "<Default text>");
    });
    m_branch.AddPoint("$0", markup, handlers);
}

void AdvGame::Update()
{
    const StoryPoint* head = m_branch.GetHead();
    m_io->WriteLine(head->GetText());
    std::string input = m_prompt.PromptInput();
    m_response.HandleInput(input);

    if (head != m_branch.GetHead())
    {
        m_response.ClearHandlers();
        m_response.AddHandlers(m_branch.GetHead()->GetHandlers());
    }
}

GameState& AdvGame::GetState()
{
    return m_state;
}

StoryBranch& AdvGame::GetStory()
{
    return m_branch;
}

IO* AdvGame::GetIO() const
{
    return m_io;
}

} // namespace txt
