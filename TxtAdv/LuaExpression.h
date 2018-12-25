/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Expression.h"
#include "LuaManager.h"

namespace txt
{

/* Class: LuaExpression
 * Implements expression handling via Lua.
 *
 * Extends:
 *
 *    <Expression>
 */
class LuaExpression : public Expression
{
public:
    /* Constructor: LuaExpression
     *
     * Parameters:
     *
     *    manager - A pointer to the <LuaManager> handling the Lua state
     *    filename - The name of the file containing the Lua function
     *    funcname - The name of the function
     */
    LuaExpression(LuaManager* manager, const std::string& filename, const std::string& funcname);
    ~LuaExpression();
private:
    LuaManager* m_manager;
    std::string m_filename;
    std::string m_funcname;

    std::string ExecImpl() const override;
};

} // namespace txt
