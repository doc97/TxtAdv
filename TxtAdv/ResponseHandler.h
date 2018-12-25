/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

/* Interface: ResponseHandler
 * Used to implement response handling for text input.
 */
class ResponseHandler
{
public:
    virtual ~ResponseHandler() {}

    /* Function: HandleInput
     * Implement input handling code here.
     *
     * Parameters:
     *
     *    input - The input to handle
     */
    inline void HandleInput(const std::string& input)
    {
        HandleInputImpl(input);
    }

    /* Function: Matches
     * Implement matching functionality here.
     *
     * Parameters:
     *
     *    input - Input to check for match
     */
    inline bool Matches(const std::string& input)
    {
        return MatchesImpl(input);
    }

private:
    virtual void HandleInputImpl(const std::string& input) = 0;
    virtual bool MatchesImpl(const std::string& input) = 0;
};

} // namespace txt
