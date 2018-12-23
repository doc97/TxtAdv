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
    virtual void HandleInput(const std::string& input) = 0;

    /* Function: Matches
     * Implement matching functionality here.
     *
     * Parameters:
     *
     *    input - Input to check for match
     */
    virtual bool Matches(const std::string& input) = 0;
};

} // namespace txt
