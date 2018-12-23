/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include "ResponseHandler.h"
#include "LuaManager.h"

namespace txt
{

/* Class: LuaResponseHandler
 * Implements response handling via Lua.
 *
 * Extends:
 *
 *    <ResponseHandler>
 */
class LuaResponseHandler : public ResponseHandler
{
public:
    /* Constructor: LuaResponseHandler
     *
     * Parameters:
     *
     *    manager - A pointer to the <LuaManager> handling the Lua state
     *    filename - The name of the file containing the Lua handler functions
     */
    LuaResponseHandler(LuaManager* manager, const std::string& filename);
    ~LuaResponseHandler();

    /* Function: HandleInput
     * If <Matches> returns true, calls the _action_ function defined in Lua.
     *
     * Parameters:
     *
     *    input - The input on which to run the _action_ function
     */
    void HandleInput(const std::string& input) override;

    /* Function: Matches
     * Checks whether the input is acceptable by calling the _matches_ function defined in Lua.
     *
     * Parameters:
     *
     *    input - The input on which to run the _matches_ function
     */
    bool Matches(const std::string& input) override;
private:
    LuaManager* m_manager;
    std::string m_filename;
};

} // namespace txt
