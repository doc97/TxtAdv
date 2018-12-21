#pragma once

#include <string>
#include "LuaManager.h"

class LuaResponseHandler
{
public:
    LuaResponseHandler(LuaManager* manager, const std::string& filename);
    ~LuaResponseHandler();

    void HandleInput(const std::string& input);
    bool Matches(const std::string& input);
private:
    LuaManager* m_manager;
    std::string m_filename;
};

