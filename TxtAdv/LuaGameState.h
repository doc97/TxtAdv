#pragma once

#include "LunaFive.h"
#include "GameState.h"

class LuaGameState
{
public:
    LuaGameState(GameState* state);
    ~LuaGameState();
    void setStr(const std::string& key, const std::string& value);

    // Lua interface
    static const char* className;
    static const Luna<LuaGameState>::FunctionType methods[];
    static const Luna<LuaGameState>::PropertyType properties[];

    bool isExisting = false;
    bool isPrecious = false;

    LuaGameState(lua_State* L);
    int setStr(lua_State* L);
private:
    GameState* m_state;

    static LuaGameState* GetObj(lua_State* L, int index);
};

