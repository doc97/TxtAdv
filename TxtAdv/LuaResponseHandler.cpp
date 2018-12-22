/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaResponseHandler.h"

namespace txt
{

LuaResponseHandler::LuaResponseHandler(LuaManager* manager, const std::string& filename)
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
        if (!m_manager->ExecFunc(m_filename.c_str(), "action", params, retVal, err))
            throw std::runtime_error(err);
    }
}

bool LuaResponseHandler::Matches(const std::string& input)
{
    std::string err;
    std::vector<LuaParam> params = { { LuaParam::String, input.c_str() } };
    std::vector<LuaParam> retVal = { { LuaParam::Bool, false } };
    if (!m_manager->ExecFunc(m_filename.c_str(), "matches", params, retVal, err))
        throw std::runtime_error(err);
    return retVal[0].data.b;
}

} // namespace txt
