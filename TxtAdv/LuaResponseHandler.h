#pragma once

#include <string>
#include "LuaManager.h"

class LuaResponseHandler
{
public:
    LuaResponseHandler(std::shared_ptr<LuaManager> manager, const std::string& filename);
    ~LuaResponseHandler();

    void HandleInput(const std::string& input);
    bool Matches(const std::string& input);
private:
    std::shared_ptr<LuaManager> m_manager;
    std::string m_filename;
};

