#pragma once

#include <string>

class InputHandler
{
public:
    virtual ~InputHandler() {}
    virtual void HandleInput(const std::string& input) = 0;
    virtual bool Matches(const std::string& input) = 0;
};

