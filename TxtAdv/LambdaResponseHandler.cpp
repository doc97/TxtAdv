/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LambdaResponseHandler.h"

namespace txt
{

LambdaResponseHandler::LambdaResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
    const std::function<void(const ResponseMatch&)>& func)
    : m_matcher(matcher), m_func(func)
{
}

LambdaResponseHandler::~LambdaResponseHandler()
{
}

void LambdaResponseHandler::HandleInputImpl(const std::string& input)
{
    ResponseMatch match = m_matcher(input);
    if (match.IsMatch())
        m_func(match);
}

bool LambdaResponseHandler::MatchesImpl(const std::string& input)
{
    return m_matcher(input).IsMatch();
}

} // namespace txt
