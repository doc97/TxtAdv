#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(const std::function<bool(const std::string&)>& matcher, const std::function<void()>& func)
    : m_matcher(matcher), m_func(func)
{
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::HandleInput(const std::string& input)
{
    if (m_matcher(input))
        m_func();
}

std::function<bool(const std::string&)> ResponseHandler::GetMatcher()
{
    return m_matcher;
}
