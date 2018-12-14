#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "InputListener.h"

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void Bind(const std::string& key, InputListener* listener);
    void HandleInput(const std::string& input);

private:
    std::unordered_map<std::string, std::vector<InputListener*>> handlers;
};

