#pragma once

#include "LunaFive.h"
#include "GameState.h"

class LuaGameState
{
public:
    LuaGameState(GameState* state);
    ~LuaGameState();
    void SetStr(const std::string& key, const std::string& value);
    std::string GetStr(const std::string& key);
    void SetFloat(const std::string& key, float value);
    float GetFloat(const std::string& key);
    void SetInt(const std::string& key, int value);
    int GetInt(const std::string& key);
    bool HasStr(const std::string& key);
    bool HasFloat(const std::string& key);
    bool HasInt(const std::string& key);

    // Lua interface
    static const char* className;
    static const Luna<LuaGameState>::FunctionType methods[];
    static const Luna<LuaGameState>::PropertyType properties[];

    bool isExisting = false;
    bool isPrecious = false;

    LuaGameState(lua_State* L);
    int setStr(lua_State* L);
    int getStr(lua_State* L);
    int hasStr(lua_State* L);
    int setFloat(lua_State* L);
    int getFloat(lua_State* L);
    int hasFloat(lua_State* L);
    int setInt(lua_State* L);
    int getInt(lua_State* L);
    int hasInt(lua_State* L);
private:
    GameState* m_state = nullptr;

    static LuaGameState* GetObj(lua_State* L, int index);
};

