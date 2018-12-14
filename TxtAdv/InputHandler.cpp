#include "InputHandler.h"

typedef std::unordered_map<std::string, std::vector<InputListener*>> HandlerMap;

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::Bind(const std::string& key, InputListener* listener)
{
    handlers[key].push_back(listener);
}

void InputHandler::HandleInput(const std::string& input)
{
    HandlerMap::iterator it = handlers.find(input);
    if (it != handlers.end())
        for (InputListener* listener : it->second)
            listener->Act();
}
