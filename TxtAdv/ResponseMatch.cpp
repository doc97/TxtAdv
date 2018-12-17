#include "ResponseMatch.h"

ResponseMatch::ResponseMatch(bool isMatch, const std::vector<std::string>& captures)
    : m_isMatch(isMatch), m_captures(captures)
{
}

ResponseMatch::ResponseMatch(bool isMatch)
    : m_isMatch(isMatch)
{
}

ResponseMatch::~ResponseMatch()
{
}

bool ResponseMatch::IsMatch() const
{
    return m_isMatch;
}

size_t ResponseMatch::CaptureCount() const
{
    return m_captures.size();
}

std::string ResponseMatch::GetCapture(size_t index) const
{
    if (index >= m_captures.size())
        throw std::out_of_range("index is out of range");
    return m_captures[index];
}
