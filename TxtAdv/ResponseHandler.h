#pragma once

#include <functional>
#include <string>
#include "InputHandler.h"
#include "ResponseMatch.h"

class ResponseHandler : public InputHandler
{
public:
    ResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
        const std::function<void(const ResponseMatch&)>& func);
    ~ResponseHandler();

    void HandleInput(const std::string& input) override;
    bool Matches(const std::string&) override;
private:
    std::function<ResponseMatch(const std::string&)> m_matcher;
    std::function<void(const ResponseMatch&)> m_func;
};

