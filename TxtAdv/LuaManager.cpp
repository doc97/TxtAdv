/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaManager.h"

namespace txt
{

LuaManager::LuaManager()
    : L(nullptr)
{
    Init();
}

LuaManager::~LuaManager()
{
    lua_close(L);
}

LuaManager& LuaManager::operator=(const LuaManager& other)
{
    if (this != &other)
    {
        lua_State* newL = luaL_newstate();
        lua_close(L);
        L = newL;
    }
    return *this;
}

void LuaManager::Reset()
{
    // Clear stack
    lua_settop(L, 0);
}

void LuaManager::Init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
}

void LuaManager::GetError(std::string& error)
{
    const char* msg = lua_tostring(L, -1);
    lua_pop(L, 1);
    if (msg)
        error.assign(msg);
}

void LuaManager::RegisterFunc(const char* funcname, lua_CFunction func)
{
    lua_register(L, funcname, func);
}

void LuaManager::RegisterLib(const char* libname, const luaL_Reg lib[], int nlib)
{
    lua_createtable(L, 0, nlib);
    luaL_setfuncs(L, lib, 0);
    lua_setglobal(L, libname);
}

bool LuaManager::ExecFile(const char* filename, std::string& error)
{
    if (luaL_dofile(L, filename) != LUA_OK)
    {
        GetError(error);
        return false;
    }
    return true;
}

bool LuaManager::ExecFunc(const char* filename, const char* funcname, const std::vector<LuaParam>& params,
    std::vector<LuaParam>& retValues, std::string& error)
{
    if (!ExecFile(filename, error))
        return false;

    // Push function onto the stack
    lua_getglobal(L, funcname);
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1); // Pop it back manually
        error = std::string("ERROR: '" + std::string(funcname) + "' is not the name of any known function!");
        return false;
    }

    LoadParams(params);

    // Pops stack automatically
    if (lua_pcall(L, (int)params.size(), retValues.size(), 0) != LUA_OK)
    {
        GetError(error);
        return false;
    }
    for (size_t i = 0; i < retValues.size(); ++i)
    {
        bool isCorrectType = false;
        LuaParam param = { LuaParam::Bool, false };
        param.type = retValues[i].type;
        switch (retValues[i].type)
        {
        case LuaParam::Bool:
            isCorrectType = lua_isboolean(L, -1);
            retValues[i] = { LuaParam::Bool, static_cast<bool>(lua_toboolean(L, -1)) };
            lua_pop(L, 1);
            break;
        case LuaParam::Int:
            isCorrectType = lua_isinteger(L, -1);
            retValues[i] = { LuaParam::Int, static_cast<long long>(lua_tointeger(L, -1)) };
            lua_pop(L, 1);
            break;
        case LuaParam::Double:
            isCorrectType = lua_isnumber(L, -1);
            retValues[i] = { LuaParam::Double, static_cast<double>(lua_tonumber(L, -1)) };
            lua_pop(L, 1);
            break;
        case LuaParam::String:
            isCorrectType = lua_isstring(L, -1);
            retValues[i] = { LuaParam::String, static_cast<const char*>(lua_tostring(L, -1)) };
            lua_pop(L, 1);
            break;
        }

        if (!isCorrectType)
        {
            error = "ERROR: Lua function returned an unknown type (index " + std::to_string(i) + ")";
            return false;
        }
    }
    return true;
}

void LuaManager::LoadParams(const std::vector<LuaParam>& params)
{
    for (const LuaParam& p : params)
        LoadParam(p);
}

void LuaManager::LoadParam(const LuaParam& param)
{
    switch (param.type)
    {
    case LuaParam::Bool: lua_pushboolean(L, param.data.b); break;
    case LuaParam::Int: lua_pushinteger(L, param.data.i); break;
    case LuaParam::Double: lua_pushnumber(L, param.data.d); break;
    case LuaParam::String: lua_pushstring(L, param.data.s); break;
    }
}

} // namespace txt
