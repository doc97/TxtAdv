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

    /* Function: HandleInput
     * If <Matches> return true, calls the lambda expression containing action functionality.
     *
     * Parameters:
     *
     *    input - The input on which to run the lambda expressions
     */
    void HandleInput(const std::string& input) override;

    /* Function: Matches
     * Checks whether the input is acceptable by using a lambda expression.
     *
     * Parameters:
     *
     *    input - The input on which to run the matcher lambda expression
     */
    bool Matches(const std::string& input) override;
private:
    std::function<ResponseMatch(const std::string&)> m_matcher;
    std::function<void(const ResponseMatch&)> m_func;
};

}
