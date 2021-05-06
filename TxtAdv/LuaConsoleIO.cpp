#include "LuaConsoleIO.h"
#include "LuaUtils.h"

namespace txt
{

const char* LuaConsoleIO::className = "LuaConsoleIO";
const Luna<LuaConsoleIO>::FunctionType LuaConsoleIO::methods[] =
{
    { "writeLine", &LuaConsoleIO::writeLine },
    {NULL, NULL}
};
const Luna<LuaConsoleIO>::PropertyType LuaConsoleIO::properties[] =
{
    {NULL, NULL}
};

LuaConsoleIO::LuaConsoleIO(lua_State* L)
    : m_io(nullptr)
{
}
LuaConsoleIO::LuaConsoleIO(ConsoleIO* io)
    : m_io(io)
{
}

LuaConsoleIO::~LuaConsoleIO()
{
}

void LuaConsoleIO::WriteLine(const std::string& line)
{
    m_io->WriteLine(line);
}

/*** LUA INTERFACE ***/

int LuaConsoleIO::writeLine(lua_State* L)
{
    LuaConsoleIO* io = GetObj<LuaConsoleIO>(L, 1, className);
    io->WriteLine(GetString(L, 2));
    return 0;
}

} // namespace txt
