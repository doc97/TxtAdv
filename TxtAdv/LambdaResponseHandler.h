/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <functional>
#include "ResponseHandler.h"
#include "ResponseMatch.h"

namespace txt
{

class LambdaResponseHandler : public ResponseHandler
{
public:
    LambdaResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
        const std::function<void(const ResponseMatch&)>& func);
    ~LambdaResponseHandler();

    void HandleInput(const std::string& input) override;
    bool Matches(const std::string&) override;
private:
    std::function<ResponseMatch(const std::string&)> m_matcher;
    std::function<void(const ResponseMatch&)> m_func;
};

}
