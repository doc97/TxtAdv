#pragma once

#include <string>
#include "ResponseHandler.h"
#include "LuaManager.h"

namespace txt
{

class LuaResponseHandler : public ResponseHandler
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

} // namespace txt
