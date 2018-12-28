/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "LunaFive.h"
#include "StoryBranch.h"

namespace txt
{

/* Class: LuaStoryBranch
 * Lua wrapper class for <StoryBranch>.
 *
 * See Also:
 *    <StoryBranch>
 */
class LuaStoryBranch
{
public:
    /* Constructor: LuaStoryBranch
     *
     * Parameters:
     *
     *    branch - A pointer to the <StoryBranch> to wrap
     */
    LuaStoryBranch(StoryBranch* branch);
    ~LuaStoryBranch();

    /* Function: Next
     * Wrapper for <StoryBranch::Next>
     */
    void Next();

    /* Function: Prev
     * Wrapper for <StoryBranch::Prev>
     */
    void Prev();

    /********** LUA INTERFACE **********/

    /* Constant: className
     * The name used for this class in Lua.
     */
    static const char* className;

    /* Constant: methods
     * An array of methods exposed to Lua.
     */
    static const Luna<LuaStoryBranch>::FunctionType methods[];

    /* Constant: properties
     * An array of properties exposed to Lua.
     */
    static const Luna<LuaStoryBranch>::PropertyType properties[];

    /* Constructor: LuaStoryBranch
     * Will be called from Lua code.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    LuaStoryBranch(lua_State* L);

    /* Function: next
     * Expose <Next> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int next(lua_State* L);

    /* Function: prev
     * Expose <Prev> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int prev(lua_State* L);
private:
    StoryBranch* m_branch;

    static LuaStoryBranch* GetObj(lua_State* L, int index);
};

} // namespace txt
