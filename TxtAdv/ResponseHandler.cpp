#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
    const std::function<void()>& func)
    : m_matcher(matcher), m_func(func)
{
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::HandleInput(const std::string& input)
{
    ResponseMatch match = m_matcher(input);
    if (match.IsMatch())
        m_func();
}

std::function<ResponseMatch(const std::string&)> ResponseHandler::GetMatcher()
{
    return m_matcher;
}
