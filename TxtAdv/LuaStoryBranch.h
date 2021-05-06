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

    /* Function: Head
     * Wrapper for <StoryBranch::Head>
     */
    int Head();

    /* Function: SetHead
     * Wrapper for <StoryBranch::SetHead>
     */
    void SetHead(unsigned int index);

    /* Function: SetHead
     * Wrapper for <StoryBranch::SetHead>
     */
    void SetHeadByName(const std::string& name);

    /* Function: IsAtStart
     * Wrapper for <StoryBranch::IsAtStart>
     */
    bool IsAtStart();

    /* Function: IsAtEnd
     * Wrapper for <StoryBranch::IsAtEnd>
     */
    bool IsAtEnd();

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

    /* Function: head
     * Expose <Head> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int head(lua_State* L);

    /* Function: setHead
     * Expose <SetHead> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int setHead(lua_State* L);

    /* Function: setHeadByName
     * Expose <SetHeadByName> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int setHeadByName(lua_State* L);

    /* Function: is_at_start
     * Expose <IsAtStart> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int isAtStart(lua_State* L);

    /* Function: is_at_end
     * Expose <IsAtEnd> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int isAtEnd(lua_State* L);
private:
    StoryBranch* m_branch;
};

} // namespace txt
