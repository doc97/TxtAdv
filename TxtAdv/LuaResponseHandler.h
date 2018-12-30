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
    LuaResponseHandler(LuaManager* manager, const std::string& filename,
        const std::string& matcher="matches", const std::string& action="action");
    ~LuaResponseHandler();

private:
    LuaManager* m_manager;
    std::string m_filename;
    std::string m_func_matcher;
    std::string m_func_action;

    void HandleInputImpl(const std::string& input) override;
    bool MatchesImpl(const std::string& input) override;
};

} // namespace txt
