#include "LuaResponseHandler.h"

LuaResponseHandler::LuaResponseHandler(std::shared_ptr<LuaManager> manager, const std::string& filename)
    : m_manager(manager), m_filename(filename)
{
}

LuaResponseHandler::~LuaResponseHandler()
{
}

void LuaResponseHandler::HandleInput(const std::string& input)
{
    if (Matches(input))
    {
        std::string err;
        std::vector<LuaParam> params = { { LuaParam::String, input.c_str() } };
        std::vector<LuaParam> retVal = {};
        m_manager->ExecFunc(m_filename.c_str(), "action", params, retVal, err);
    }
}

bool LuaResponseHandler::Matches(const std::string& input)
{
    std::string err;
    std::vector<LuaParam> params = { { LuaParam::String, input.c_str() } };
    std::vector<LuaParam> retVal = { { LuaParam::Bool, false } };
    if (!m_manager->ExecFunc(m_filename.c_str(), "matches", params, retVal, err))
        return false;
    return retVal[0].data.b;
}
