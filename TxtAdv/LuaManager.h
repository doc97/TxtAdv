#pragma once

#include <string>
#include <vector>
#include "LuaParam.h"

struct lua_State;

class LuaManager
{
public:
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager& other) = delete;
    LuaManager& operator=(const LuaManager& other);

    void Reset();
    bool Exec(const char* filename, const char* funcname, const std::vector<LuaParam>& params,
        std::string& error);
private:
    void Init();
    void GetError(std::string& error);
    void LoadParams(const std::vector<LuaParam>& params);
    void LoadParam(const LuaParam& param);

    lua_State* L;
};

