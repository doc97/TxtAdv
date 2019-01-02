/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaResponseHandler.h"

namespace txt
{

LuaResponseHandler::LuaResponseHandler(LuaManager* manager, const std::string& filename,
    const std::string& matcher, const std::string& action)
    : m_manager(manager), m_filename(filename), m_func_matcher(matcher), m_func_action(action)
{
}

LuaResponseHandler::LuaResponseHandler(const std::string& filename,
    const std::string& matcher, const std::string& action)
    : LuaResponseHandler(nullptr, filename, matcher, action)
{
}

LuaResponseHandler::~LuaResponseHandler()
{
}

void LuaResponseHandler::SetManager(LuaManager* manager)
{
    m_manager = manager;
}

void LuaResponseHandler::HandleInputImpl(const std::string& input)
{
    if (Matches(input))
    {
        std::string err;
        std::vector<LuaParam> params = { { LuaParam::String, input.c_str() } };
        std::vector<LuaParam> retVal = {};
        if (!m_manager->ExecFunc(m_filename.c_str(), m_func_action.c_str(), params, retVal, err))
            throw std::runtime_error(err);
    }
}

bool LuaResponseHandler::MatchesImpl(const std::string& input)
{
    if (!m_manager)
        throw std::runtime_error("No LuaManager has been specified!");
    std::string err;
    std::vector<LuaParam> params = { { LuaParam::String, input.c_str() } };
    std::vector<LuaParam> retVal = { { LuaParam::Bool, false } };
    if (!m_manager->ExecFunc(m_filename.c_str(), m_func_matcher.c_str(), params, retVal, err))
        throw std::runtime_error(err);
    return retVal[0].data.b;
}

} // namespace txt
