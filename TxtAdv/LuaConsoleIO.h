/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "LunaFive.h"
#include "ConsoleIO.h"

namespace txt
{

/* Class: LuaConsoleIO
 * Lua wrapper class for <ConsoleIO>.
 *
 * See Also:
 *
 *    <ConsoleIO>
 */
class LuaConsoleIO
{
public:
    /* Constructor: LuaGameState
     *
     * Parameters:
     *
     *    io - A pointer to the <ConsoleIO> to wrap
     */
    LuaConsoleIO(ConsoleIO* io);
    ~LuaConsoleIO();

    /* Function: WriteLine
     * Wrapper for <ConsoleIO::WriteLine>.
     */
    void WriteLine(const std::string& line);

    /********** LUA INTERFACE **********/

    /* Constant: className
     * The name used for this class in Lua.
     */
    static const char* className;

    /* Constant: methods
     * An array of methods exposed to Lua.
     */
    static const Luna<LuaConsoleIO>::FunctionType methods[];

    /* Constant: properties
     * An array of properties exposed to Lua.
     */
    static const Luna<LuaConsoleIO>::PropertyType properties[];

    /* Constructor: LuaConsoleIO
     * Will be called from Lua code.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    LuaConsoleIO(lua_State* L);

    /* Function: writeLine
     * Expose <WriteLine> to Lua.
     *
     * Parameters:
     *
     *    L - the Lua state
     */
    int writeLine(lua_State* L);
private:
    ConsoleIO* m_io;
};

} // namespace txt

