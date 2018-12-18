#include "LuaParam.h"
#include <assert.h>

LuaParam::LuaParam(const DataType type, void* value)
    : m_type(type), m_value(value)
{
}

LuaParam::~LuaParam()
{
}

LuaParam::DataType LuaParam::GetType() const
{
    return m_type;
}

const void* LuaParam::GetValue() const
{
    return m_value;
}
