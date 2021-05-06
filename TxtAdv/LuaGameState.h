/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "LunaFive.h"
#include "GameState.h"

namespace txt
{

/* Class: LuaGameState
 * Lua wrapper class for <GameState>.
 *
 * See Also:
 *
 *    <GameState>
 */
class LuaGameState
{
public:
    /* Constructor: LuaGameState
     *
     * Parameters:
     *
     *    state - A pointer to the <GameState> to wrap
     */
    LuaGameState(GameState* state);
    ~LuaGameState();

    /* Function: SetStr
     * Wrapper for <GameState::SetString>.
     */
    void SetStr(const std::string& key, const std::string& value);

    /* Function: GetStr
     * Wrapper for <GameState::GetString>.
     */
    std::string GetStr(const std::string& key);

    /* Function: SetFloat
     * Wrapper for <GameState::SetFloat>.
     */
    void SetFloat(const std::string& key, float value);

    /* Function: GetFloat
     * Wrapper for <GameState::GetFloat>.
     */
    float GetFloat(const std::string& key);

    /* Function: SetInt
     * Wrapper for <GameState::SetInt>.
     */
    void SetInt(const std::string& key, int value);

    /* Function: GetInt
     * Wrapper for <GameState::GetInt>.
     */
    int GetInt(const std::string& key);

    /* Function: HasStr
     * Wrapper for <GameState::HasString>.
     */
    bool HasStr(const std::string& key);

    /* Function: HasFloat
     * Wrapper for <GameState::HasFloat>.
     */
    bool HasFloat(const std::string& key);

    /* Function: HasInt
     * Wrapper for <GameState::HasInt>.
     */
    bool HasInt(const std::string& key);

    /********** LUA INTERFACE **********/

    /* Constant: className
     * The name used for this class in Lua.
     */
    static const char* className;

    /* Constant: methods
     * An array of methods exposed to Lua.
     */
    static const Luna<LuaGameState>::FunctionType methods[];

    /* Constant: properties
     * An array of properties exposed to Lua.
     */
    static const Luna<LuaGameState>::PropertyType properties[];

    /* Constructor: LuaGameState
     * Will be called from Lua code.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    LuaGameState(lua_State* L);

    /* Function: setStr
     * Expose <SetStr> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int setStr(lua_State* L);

    /* Function: getStr
     * Expose <GetStr> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int getStr(lua_State* L);

    /* Function: hasStr
     * Expose <HasStr> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int hasStr(lua_State* L);

    /* Function: setFloat
     * Expose <SetFloat> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int setFloat(lua_State* L);

    /* Function: getFloat
     * Expose <GetFloat> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int getFloat(lua_State* L);

    /* Function: hasFloat
     * Expose <HasFloat> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int hasFloat(lua_State* L);

    /* Function: setInt
     * Expose <SetInt> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int setInt(lua_State* L);

    /* Function: getInt
     * Expose <GetInt> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int getInt(lua_State* L);

    /* Function: hasInt
     * Expose <HasInt> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int hasInt(lua_State* L);
private:
    GameState* m_state;
};

}
