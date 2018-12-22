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

    void Reset();
    void RegisterFunc(const char* funcname, lua_CFunction func);
    void RegisterLib(const char* libname, const luaL_Reg lib[], size_t nlib);
    bool ExecFile(const char* filename, std::string& error);
    bool ExecFunc(const char* filename, const char* funcname, const std::vector<LuaParam>& params,
        std::vector<LuaParam>& retValues, std::string& error);

    template<typename T>
    void RegisterClass()
    {
        Luna<T>::Register(L);
    }
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

    lua_State* L;
};

} // namespace txt
