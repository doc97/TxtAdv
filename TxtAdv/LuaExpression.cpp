/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "LuaExpression.h"

namespace txt
{

LuaExpression::LuaExpression(LuaManager* manager, const std::string& filename, const std::string& funcname)
    : m_manager(manager), m_filename(filename), m_funcname(funcname)
{
}


LuaExpression::~LuaExpression()
{
}

std::string LuaExpression::ExecImpl() const
{
    std::string err;
    std::vector<LuaParam> retVal = { { LuaParam::String, "" } };
    if (m_manager->ExecFunc(m_filename, m_funcname.c_str(), {}, retVal, err))
        return retVal.at(0).data.s;
    return "";
}

} // namespace txt
