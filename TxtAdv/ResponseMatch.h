#pragma once

#include <string>
#include <vector>

namespace txt
{

class ResponseMatch
{
public:
    ResponseMatch(bool isMatch, const std::vector<std::string>& captures);
    ResponseMatch(bool isMatch);
    ~ResponseMatch();

    bool IsMatch() const;
    size_t CaptureCount() const;
    std::string GetCapture(size_t index) const;
private:
    bool m_isMatch;
    std::vector<std::string> m_captures;
};

} // namespace txt
