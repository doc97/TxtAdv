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

/* Class: LambdaResponseHandler
 * Implements response handling via lambda expressions.
 *
 * Extends:
 *
 *    <ResponseHandler>
 */
class LambdaResponseHandler : public ResponseHandler
{
public:
    /* Constructor: LambdaResponseHandler
     *
     * Parameters:
     *
     *    matcher - The lambda expression used to to implement matching functionality
     *    func - The lambda expression used to to implement action functionality
     */
    LambdaResponseHandler(const std::function<ResponseMatch(const std::string&)>& matcher,
        const std::function<void(const ResponseMatch&)>& func);
    ~LambdaResponseHandler();

private:
    std::function<ResponseMatch(const std::string&)> m_matcher;
    std::function<void(const ResponseMatch&)> m_func;

    void HandleInputImpl(const std::string& input) override;
    bool MatchesImpl(const std::string& input) override;
};

}
