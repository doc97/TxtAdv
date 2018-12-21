#pragma once

#include <string>
#include "InputHandler.h"
#include "LuaManager.h"

class LuaResponseHandler : public InputHandler
{
public:
    LuaResponseHandler(LuaManager* manager, const std::string& filename);
    ~LuaResponseHandler();

    void HandleInput(const std::string& input) override;
    bool Matches(const std::string& input) override;
private:
    LuaManager* m_manager;
    std::string m_filename;
};

