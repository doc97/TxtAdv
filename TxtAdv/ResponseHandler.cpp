#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
    const std::function<void(const ResponseMatch&)>& func)
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
        m_func(match);
}

bool ResponseHandler::Matches(const std::string& input)
{
    return m_matcher(input).IsMatch();
}
