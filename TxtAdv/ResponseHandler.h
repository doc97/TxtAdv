#pragma once

#include <functional>
#include <string>
#include "ResponseMatch.h"

class ResponseHandler
{
public:
    ResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
        const std::function<void(const ResponseMatch&)>& func);
    ~ResponseHandler();

    void HandleInput(const std::string& input);
    bool Matches(const std::string&) const;
private:
    std::function<ResponseMatch(const std::string&)> m_matcher;
    std::function<void(const ResponseMatch&)> m_func;
};

