#pragma once

#include <functional>
#include <string>
#include "ResponseListener.h"

class ResponseHandler
{
public:
    ResponseHandler(const std::function<bool(const std::string&)>& matcher, const std::function<void()>& func);
    ~ResponseHandler();

    void HandleInput(const std::string& input);
    std::function<bool(const std::string&)> GetMatcher();
private:
    std::function<bool(const std::string&)> m_matcher;
    std::function<void()> m_func;
};

