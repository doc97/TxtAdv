/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>
#include "LuaParam.h"
#include "LunaFive.h"

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

namespace txt
{

typedef int(*lua_CFunction) (lua_State *L);

class LuaManager
{
public:
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager& other) = delete;
    LuaManager& operator=(const LuaManager& other);

    /* Function: Reset
     * Clears the Lua stack.
     */
    void Reset();

    /* Function: RegisterFunc
     * Registers a global function to use from Lua.
     *
     * Parameters:
     *
     *    funcname - The name that will be used to call the function in Lua
     *    func - The C function to register
     */
    void RegisterFunc(const char* funcname, lua_CFunction func);

    /* Function: RegisterLib
     * Registers a library/module to use from Lua.
     *
     * Parameters:
     *
     *    libname - The name that will be used to reference the library/module in Lua
     *    lib - An array of C functions to register
     *    nlib - The number of C functions to register (arrays don't store their size)
     */
    void RegisterLib(const char* libname, const luaL_Reg lib[], int nlib);

    /* Function: ExecFile
     * Reads and executes a Lua file.
     *
     * Parameters:
     *
     *    filename - The name of the file
     *    error - Any error message is stored in this parameter
     *
     * Returns:
     *
     *    If an error occurred return false, otherwise true
     */
    bool ExecFile(const char* filename, std::string& error);

    /* Function: ExecFunc
     * Loads a Lua chunk (file) and executes a function from it.
     *
     * Parameters:
     *
     *    filename - The name of the file
     *    funcname - The name of the function
     *    params - A list of the parameters for the function
     *    retVals - The return values of the function call are put into this list
     *    error - Any error message is stored in this parameter
     *
     * Returns:
     *
     *    If an error occurred return false, otherwise true
     */
    bool ExecFunc(const char* filename, const char* funcname, const std::vector<LuaParam>& params,
        std::vector<LuaParam>& retValues, std::string& error);

    /* Function: RegisterClass
     * Registers a class to Lua.
     *
     * Template type:
     *
     *    T - The class to register
     */
    template<typename T>
    void RegisterClass()
    {
        Luna<T>::Register(L);
    }

    /* Function: PushObject
     * Push a new class instance to the global namespace in Lua.
     *
     * Parameters:
     *
     *    obj - A pointer to the object to push
     *    name - The name with which Lua can access the object
     *    gc - Whether the object should be deleted when Lua does garbage collection (default: false)
     *
     * Template type:
     *
     *    T - The class to register
     *
     * Example:
     *
     * --- C++ ---
     * Foo foo;
     * LuaManager::PushObject(&foo, "foo1");
     * LuaManager::PushObject(new Foo, "foo2", true);
     * -----------
     */
    template<typename T>
    void PushObject(T* obj, const std::string& name, bool gc = false)
    {
        Luna<T>::new_global(L, obj, name.c_str(), gc);
    }
private:
    void Init();
    void GetError(std::string& error);
    void LoadParams(const std::vector<LuaParam>& params);
    void LoadParam(const LuaParam& param);

    lua_State* L = nullptr;
};

} // namespace txt
