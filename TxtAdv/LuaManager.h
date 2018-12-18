#pragma once

struct lua_State;

class LuaManager
{
public:
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager& other) = delete;
    LuaManager& operator=(const LuaManager& other);

    void Reset();
    bool Exec(const char* filename, const char* funcname);
private:
    void Init();

    lua_State* L;
};

