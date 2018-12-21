#pragma once

#include <string>

class ResponseHandler
{
public:
    virtual ~ResponseHandler() {}
    virtual void HandleInput(const std::string& input) = 0;
    virtual bool Matches(const std::string& input) = 0;
};

